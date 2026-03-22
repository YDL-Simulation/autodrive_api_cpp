#include "metacar/sockets.hpp"

#include "metacar/logging.hpp"

#include <cstring>
#include <stdexcept>

#ifdef _WIN32
#pragma comment(lib, "ws2_32.lib")

namespace {
struct WinsockInit {
  WinsockInit() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
      throw std::runtime_error("WSAStartup failed");
    }
  }
  ~WinsockInit() { WSACleanup(); }
};
// Ensure WSAStartup is called once before any socket operations.
static WinsockInit winsock_init;
} // anonymous namespace

static void close_socket(socket_t s) {
  if (s != INVALID_SOCK)
    closesocket(s);
}

#else // POSIX

static void close_socket(socket_t s) {
  if (s != INVALID_SOCK)
    ::close(s);
}

#endif

namespace metacar {

// ── RawSocket ────────────────────────────────────────────────────────────────

RawSocket::RawSocket(const std::string &host, int port) : host_(host), port_(port) {
  server_sock_ = ::socket(AF_INET, SOCK_STREAM, 0);
  if (server_sock_ == INVALID_SOCK) {
    throw std::runtime_error("Failed to create socket");
  }

  // Allow port reuse
  int opt = 1;
#ifdef _WIN32
  setsockopt(server_sock_, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&opt),
             sizeof(opt));
#else
  setsockopt(server_sock_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(static_cast<uint16_t>(port_));
  inet_pton(AF_INET, host_.c_str(), &addr.sin_addr);

  if (::bind(server_sock_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0) {
    close_socket(server_sock_);
    server_sock_ = INVALID_SOCK;
    throw std::runtime_error("Failed to bind to " + host_ + ":" + std::to_string(port_));
  }

  if (::listen(server_sock_, 1) != 0) {
    close_socket(server_sock_);
    server_sock_ = INVALID_SOCK;
    throw std::runtime_error("Failed to listen on " + host_ + ":" + std::to_string(port_));
  }

  detail::log(LogLevel::INFO, "Listening on " + host_ + ":" + std::to_string(port_));
}

RawSocket::~RawSocket() { close(); }

void RawSocket::accept() {
  if (client_sock_ != INVALID_SOCK) {
    close_socket(client_sock_);
    client_sock_ = INVALID_SOCK;
  }

  sockaddr_in client_addr{};
#ifdef _WIN32
  int addr_len = sizeof(client_addr);
#else
  socklen_t addr_len = sizeof(client_addr);
#endif
  client_sock_ = ::accept(server_sock_, reinterpret_cast<sockaddr *>(&client_addr), &addr_len);
  if (client_sock_ == INVALID_SOCK) {
    throw std::runtime_error("Failed to accept connection");
  }

  char addr_str[INET_ADDRSTRLEN];
  inet_ntop(AF_INET, &client_addr.sin_addr, addr_str, sizeof(addr_str));
  detail::log(LogLevel::INFO, std::string(host_) + ":" + std::to_string(port_) + " connected to " +
                                  addr_str + ":" + std::to_string(ntohs(client_addr.sin_port)));
}

void RawSocket::send(const std::string &data) {
  if (client_sock_ == INVALID_SOCK) {
    throw std::runtime_error("No client connection");
  }

  uint32_t len = htonl(static_cast<uint32_t>(data.size()));
  const char *len_ptr = reinterpret_cast<const char *>(&len);

  // Send length prefix
  int total_sent = 0;
  while (total_sent < HEADER_SIZE) {
    int sent = ::send(client_sock_, len_ptr + total_sent, HEADER_SIZE - total_sent, 0);
    if (sent <= 0)
      throw std::runtime_error("Send failed (header)");
    total_sent += sent;
  }

  // Send body
  total_sent = 0;
  int body_size = static_cast<int>(data.size());
  while (total_sent < body_size) {
    int sent = ::send(client_sock_, data.data() + total_sent, body_size - total_sent, 0);
    if (sent <= 0)
      throw std::runtime_error("Send failed (body)");
    total_sent += sent;
  }
}

std::string RawSocket::receive() {
  if (client_sock_ == INVALID_SOCK) {
    throw std::runtime_error("No client connection");
  }

  std::string header = recv_exact(HEADER_SIZE);
  if (header.empty())
    return {};

  uint32_t net_len;
  std::memcpy(&net_len, header.data(), HEADER_SIZE);
  uint32_t msg_len = ntohl(net_len);

  return recv_exact(static_cast<int>(msg_len));
}

std::string RawSocket::recv_exact(int size) {
  std::string buf;
  buf.resize(static_cast<size_t>(size));
  int received = 0;
  while (received < size) {
    int n = ::recv(client_sock_, buf.data() + received, size - received, 0);
    if (n <= 0)
      return {};
    received += n;
  }
  return buf;
}

void RawSocket::close() {
  close_socket(client_sock_);
  client_sock_ = INVALID_SOCK;
  close_socket(server_sock_);
  server_sock_ = INVALID_SOCK;
}

// ── ModelSocket ──────────────────────────────────────────────────────────────

ModelSocket::ModelSocket(const std::string &host, int port) : raw_socket_(host, port) {}

void ModelSocket::accept() { raw_socket_.accept(); }
void ModelSocket::close() { raw_socket_.close(); }

nlohmann::json ModelSocket::receive_json() {
  std::string raw = raw_socket_.receive();
  if (raw.empty()) {
    throw ConnectionClosedError("Connection closed");
  }
  return nlohmann::json::parse(raw);
}

// ── StreamingSocket ──────────────────────────────────────────────────────────

StreamingSocket::StreamingSocket(const std::string &host, int port) : raw_socket_(host, port) {}

void StreamingSocket::accept() { raw_socket_.accept(); }
void StreamingSocket::close() { raw_socket_.close(); }

std::vector<uint8_t> StreamingSocket::receive_frame() {
  std::string raw = raw_socket_.receive();
  if (raw.empty()) {
    throw ConnectionClosedError("Connection closed");
  }
  return std::vector<uint8_t>(raw.begin(), raw.end());
}

} // namespace metacar

#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
using socket_t = SOCKET;
constexpr socket_t INVALID_SOCK = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using socket_t = int;
constexpr socket_t INVALID_SOCK = -1;
#endif

namespace metacar {

class ConnectionClosedError : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

/// Low-level TCP server socket with 4-byte big-endian length-prefixed messages.
/// Supports a single client connection at a time.
class RawSocket {
public:
  RawSocket(const std::string &host, int port);
  ~RawSocket();

  RawSocket(const RawSocket &) = delete;
  RawSocket &operator=(const RawSocket &) = delete;

  void accept();
  void send(const std::string &data);
  std::string receive();
  void close();

private:
  static constexpr int HEADER_SIZE = 4;

  std::string recv_exact(int size);

  std::string host_;
  int port_;
  socket_t server_sock_ = INVALID_SOCK;
  socket_t client_sock_ = INVALID_SOCK;
};

/// JSON-serializing socket built on RawSocket.
class ModelSocket {
public:
  ModelSocket(const std::string &host, int port);

  void accept();
  void close();

  template <typename T> void send(const T &data) {
    nlohmann::json j = data;
    std::string payload = j.dump();
    raw_socket_.send(payload);
  }

  template <typename T> T receive() {
    std::string raw = raw_socket_.receive();
    if (raw.empty()) {
      throw ConnectionClosedError("Connection closed");
    }
    nlohmann::json j = nlohmann::json::parse(raw);
    return j.get<T>();
  }

  /// Receive raw JSON and return the parsed json object.
  nlohmann::json receive_json();

private:
  RawSocket raw_socket_;
};

/// One-way streaming socket for receiving raw frame bytes (e.g. JPEG).
/// No OpenCV dependency — returns raw bytes.
class StreamingSocket {
public:
  StreamingSocket(const std::string &host, int port);

  void accept();
  void close();

  /// Receive a frame as raw bytes (e.g. JPEG-encoded).
  std::vector<uint8_t> receive_frame();

private:
  RawSocket raw_socket_;
};

} // namespace metacar

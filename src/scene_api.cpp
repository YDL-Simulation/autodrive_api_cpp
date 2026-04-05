#include "metacar/scene_api.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>

#include "metacar/logging.hpp"

namespace metacar {

SceneAPI::SceneAPI() : model_socket_("127.0.0.1", 5061), streaming_socket_("127.0.0.1", 5063) {}

void SceneAPI::load_static_data(const Code1 &code1) {
  const auto &map_info = code1.map_info;
  std::filesystem::path dir_path(map_info.path);

  // Read route file
  std::vector<Vector3> route;
  {
    auto route_path = dir_path / map_info.route;
    std::ifstream ifs(route_path, std::ios::binary);
    if (ifs) {
      std::ostringstream oss;
      oss << ifs.rdbuf();
      auto j = nlohmann::json::parse(oss.str());
      route = j.get<std::vector<Vector3>>();
    }
  }

  // Read map file
  std::vector<RoadInfo> roads;
  {
    auto map_path = dir_path / map_info.map;
    std::ifstream ifs(map_path, std::ios::binary);
    if (ifs) {
      std::ostringstream oss;
      oss << ifs.rdbuf();
      auto j = nlohmann::json::parse(oss.str());
      roads = j.get<std::vector<RoadInfo>>();
    }
  }

  scene_static_data_.route = std::move(route);
  scene_static_data_.roads = std::move(roads);
  scene_static_data_.sub_scenes = map_info.sub_scenes;
  scene_static_data_.vla_extension = code1.vla_extension;
}

void SceneAPI::connect() {
  model_socket_.accept();
  streaming_socket_.accept();

  Code1 code1 = model_socket_.receive<Code1>();
  load_static_data(code1);

  running_ = true;
  ready_sent_ = false;
}

const SceneStaticData &SceneAPI::get_scene_static_data() const { return scene_static_data_; }

std::optional<StepResult> SceneAPI::step() {
  if (!running_)
    return std::nullopt;

  // Send Code2 (ready) on first step
  if (!ready_sent_) {
    model_socket_.send(Code2{.code = 2});
    ready_sent_ = true;
  }

  try {
    nlohmann::json j = model_socket_.receive_json();
    int code = j.at("code").get<int>();

    if (code == 5) {
      // Scene ended
      detail::log(LogLevel::INFO, "Scene ended");
      running_ = false;
      model_socket_.close();
      streaming_socket_.close();
      return std::nullopt;
    }

    if (code == 3) {
      Code3 msg = j.get<Code3>();
      std::vector<CameraFrame> frames;
      for (const auto &cam : msg.sim_car_msg.sensor.ego_rgb_cams) {
        frames.push_back(CameraFrame{.id = cam.id, .data = streaming_socket_.receive_frame()});
      }
      return StepResult{.sim_car_msg = std::move(msg.sim_car_msg),
                         .frames = std::move(frames)};
    }

    // Unexpected code
    detail::log(LogLevel::WARN, "Unexpected message code: " + std::to_string(code));
    return std::nullopt;

  } catch (const ConnectionClosedError &) {
    detail::log(LogLevel::ERR, "Connection closed, exiting");
    running_ = false;
    model_socket_.close();
    streaming_socket_.close();
    return std::nullopt;
  }
}

void SceneAPI::set_vehicle_control(const VehicleControl &vc,
                                   const std::optional<VLAExtensionOutput> &vla_extension) {
  auto dto = VehicleControlDTO::from_control(vc, move_to_start_, move_to_end_);
  SimCarMsgOutput output{.vehicle_control = dto, .vla_extension = vla_extension};
  Code4 code4{.code = 4, .sim_car_msg = output};
  model_socket_.send(code4);
}

void SceneAPI::retry_level() {
  ++move_to_start_;
  detail::log(LogLevel::INFO, "Retry level");
}

void SceneAPI::skip_level() {
  ++move_to_end_;
  detail::log(LogLevel::INFO, "Skip level");
}

bool SceneAPI::is_running() const { return running_; }

} // namespace metacar

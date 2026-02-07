#pragma once

#include <optional>
#include <string>
#include <vector>

#include "metacar/models.hpp"
#include "metacar/sockets.hpp"

namespace metacar {

/// High-level interface for communicating with the simulation environment.
///
/// Usage: create instance -> connect() -> get_scene_static_data()
///        -> loop: step() + set_vehicle_control()
class SceneAPI {
public:
    SceneAPI();

    /// Block until the simulation connects, then load static data.
    void connect();

    /// Get the scene static data (available after connect()).
    const SceneStaticData& get_scene_static_data() const;

    /// Single-step: get the next simulation frame.
    /// Returns std::nullopt when the scene ends or the connection closes.
    /// On the first call, sends Code2 (ready signal) automatically.
    std::optional<SimCarMsg> step();

    /// Send vehicle control commands to the simulation.
    void set_vehicle_control(const VehicleControl& vc,
                             const std::optional<VLAExtensionOutput>& vla_extension = std::nullopt);

    /// Request a retry of the current sub-scene.
    void retry_level();

    /// Request to skip the current sub-scene.
    void skip_level();

    /// Check whether the simulation loop is still active.
    bool is_running() const;

private:
    void load_static_data(const Code1& code1);

    int move_to_start_ = 0;
    int move_to_end_ = 0;
    bool ready_sent_ = false;
    bool running_ = false;

    ModelSocket model_socket_;
    StreamingSocket streaming_socket_;
    SceneStaticData scene_static_data_;
};

} // namespace metacar

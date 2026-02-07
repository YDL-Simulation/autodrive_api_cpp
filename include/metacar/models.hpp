#pragma once

#include <optional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "metacar/geometry.hpp"

namespace metacar {

// ── Enumerations ─────────────────────────────────────────────────────────────

enum class RegionType {
  NORMAL_PARKING = 0,
  RESTRICTED_PARKING = 1,
  FUNCTION_ZONE = 2,
};

enum class LineType {
  MIDDLE_LINE = 1,
  SIDE_LINE = 2,
  SOLID_LINE = 3,
  STOP_LINE = 4,
  ZEBRA_CROSSING = 5,
  DASH_LINE = 6,
};

enum class DrivingType {
  MOTOR_VEHICLE_ALLOWED = 1,
  NON_MOTOR_VEHICLE_ALLOWED = 2,
  PEDESTRIAN_ALLOWED = 3,
};

enum class TrafficSignType {
  NO_SIGN = 0,
  SPEED_LIMIT_SIGN = 1,
  STOP_SIGN = 2,
  V2X_SIGN = 3,
};

enum class GearMode {
  NEUTRAL = 0,
  DRIVE = 1,
  REVERSE = 2,
  PARKING = 3,
};

enum class ObstacleType {
  UNKNOWN = 0,
  PEDESTRIAN = 4,
  CAR = 6,
  STATIC = 7,
  BICYCLE = 8,
  ROAD_MARK = 12,
  TRAFFIC_SIGN = 13,
  TRAFFIC_LIGHT = 15,
  RIDER = 17,
  TRUCK = 18,
  BUS = 19,
  SPECIAL_VEHICLE = 20,
  MOTORCYCLE = 21,
  DYNAMIC = 22,
  SPEED_LIMIT_SIGN = 26,
  BICYCLE_STATIC = 27,
  ROAD_OBSTACLE = 29,
  PARKING_SLOT = 30,
};

enum class TrafficLightState {
  RED = 1,
  GREEN = 2,
  YELLOW = 3,
};

// Enum JSON serialization declarations
NLOHMANN_JSON_SERIALIZE_ENUM(RegionType, {
                                             {RegionType::NORMAL_PARKING, 0},
                                             {RegionType::RESTRICTED_PARKING, 1},
                                             {RegionType::FUNCTION_ZONE, 2},
                                         })

NLOHMANN_JSON_SERIALIZE_ENUM(LineType, {
                                           {LineType::MIDDLE_LINE, 1},
                                           {LineType::SIDE_LINE, 2},
                                           {LineType::SOLID_LINE, 3},
                                           {LineType::STOP_LINE, 4},
                                           {LineType::ZEBRA_CROSSING, 5},
                                           {LineType::DASH_LINE, 6},
                                       })

NLOHMANN_JSON_SERIALIZE_ENUM(DrivingType, {
                                              {DrivingType::MOTOR_VEHICLE_ALLOWED, 1},
                                              {DrivingType::NON_MOTOR_VEHICLE_ALLOWED, 2},
                                              {DrivingType::PEDESTRIAN_ALLOWED, 3},
                                          })

NLOHMANN_JSON_SERIALIZE_ENUM(TrafficSignType, {
                                                  {TrafficSignType::NO_SIGN, 0},
                                                  {TrafficSignType::SPEED_LIMIT_SIGN, 1},
                                                  {TrafficSignType::STOP_SIGN, 2},
                                                  {TrafficSignType::V2X_SIGN, 3},
                                              })

NLOHMANN_JSON_SERIALIZE_ENUM(GearMode, {
                                           {GearMode::NEUTRAL, 0},
                                           {GearMode::DRIVE, 1},
                                           {GearMode::REVERSE, 2},
                                           {GearMode::PARKING, 3},
                                       })

NLOHMANN_JSON_SERIALIZE_ENUM(ObstacleType, {
                                               {ObstacleType::UNKNOWN, 0},
                                               {ObstacleType::PEDESTRIAN, 4},
                                               {ObstacleType::CAR, 6},
                                               {ObstacleType::STATIC, 7},
                                               {ObstacleType::BICYCLE, 8},
                                               {ObstacleType::ROAD_MARK, 12},
                                               {ObstacleType::TRAFFIC_SIGN, 13},
                                               {ObstacleType::TRAFFIC_LIGHT, 15},
                                               {ObstacleType::RIDER, 17},
                                               {ObstacleType::TRUCK, 18},
                                               {ObstacleType::BUS, 19},
                                               {ObstacleType::SPECIAL_VEHICLE, 20},
                                               {ObstacleType::MOTORCYCLE, 21},
                                               {ObstacleType::DYNAMIC, 22},
                                               {ObstacleType::SPEED_LIMIT_SIGN, 26},
                                               {ObstacleType::BICYCLE_STATIC, 27},
                                               {ObstacleType::ROAD_OBSTACLE, 29},
                                               {ObstacleType::PARKING_SLOT, 30},
                                           })

NLOHMANN_JSON_SERIALIZE_ENUM(TrafficLightState, {
                                                    {TrafficLightState::RED, 1},
                                                    {TrafficLightState::GREEN, 2},
                                                    {TrafficLightState::YELLOW, 3},
                                                })

// ── VLA models ───────────────────────────────────────────────────────────────

struct BuildingInfo {
  std::string id;
  std::string name;
  double pos_x = 0.0;
  double pos_y = 0.0;
  double pos_z = 0.0;
  double ori_x = 0.0;
  double ori_y = 0.0;
  double ori_z = 0.0;
  double length = 0.0;
  double width = 0.0;
  double height = 0.0;
};

void to_json(nlohmann::json &j, const BuildingInfo &v);
void from_json(const nlohmann::json &j, BuildingInfo &v);

struct RegionInfo {
  std::string id;
  RegionType type = RegionType::NORMAL_PARKING;
  double pos_x = 0.0;
  double pos_y = 0.0;
  double pos_z = 0.0;
  double ori_x = 0.0;
  double ori_y = 0.0;
  double ori_z = 0.0;
  double length = 0.0;
  double width = 0.0;
};

void to_json(nlohmann::json &j, const RegionInfo &v);
void from_json(const nlohmann::json &j, RegionInfo &v);

struct VLAExtension {
  std::vector<BuildingInfo> buildings;
  std::vector<RegionInfo> regions;
};

void to_json(nlohmann::json &j, const VLAExtension &v);
void from_json(const nlohmann::json &j, VLAExtension &v);

struct VLATextOutput {
  std::string ocr_text;
  std::string time_phrase;
  std::string location_phrase;
  std::string action_phrase;
};

void to_json(nlohmann::json &j, const VLATextOutput &v);
void from_json(const nlohmann::json &j, VLATextOutput &v);

struct FunctionZoneViolation {
  std::string rule_code;
  std::vector<std::string> sticker_ids;
};

void to_json(nlohmann::json &j, const FunctionZoneViolation &v);
void from_json(const nlohmann::json &j, FunctionZoneViolation &v);

struct FunctionZoneResult {
  std::vector<FunctionZoneViolation> violations;
};

void to_json(nlohmann::json &j, const FunctionZoneResult &v);
void from_json(const nlohmann::json &j, FunctionZoneResult &v);

struct ParkingResult {
  std::vector<std::string> violating_sticker_ids;
};

void to_json(nlohmann::json &j, const ParkingResult &v);
void from_json(const nlohmann::json &j, ParkingResult &v);

struct VLAExtensionOutput {
  std::optional<VLATextOutput> text_info;
  std::optional<FunctionZoneResult> function_zone_result;
  std::optional<ParkingResult> parking_result;
};

void to_json(nlohmann::json &j, const VLAExtensionOutput &v);
void from_json(const nlohmann::json &j, VLAExtensionOutput &v);

// ── Scene static data models ─────────────────────────────────────────────────

struct SubSceneInfo {
  std::string name;
  std::optional<Vector3> start_point;
  std::optional<Vector3> end_point;
};

void to_json(nlohmann::json &j, const SubSceneInfo &v);
void from_json(const nlohmann::json &j, SubSceneInfo &v);

struct MapConfig {
  std::string path;
  std::string route;
  std::string map;
  std::vector<SubSceneInfo> sub_scenes;
};

void to_json(nlohmann::json &j, const MapConfig &v);
void from_json(const nlohmann::json &j, MapConfig &v);

struct BorderInfo {
  LineType type = LineType::MIDDLE_LINE;
  std::vector<Vector2> path_points;
};

void to_json(nlohmann::json &j, const BorderInfo &v);
void from_json(const nlohmann::json &j, BorderInfo &v);

struct LaneInfo {
  std::string id;
  BorderInfo left_border;
  BorderInfo right_border;
  std::string left_lane_id;
  std::string right_lane_id;
  double width = 0.0;
  std::vector<Vector2> path_points;
};

void to_json(nlohmann::json &j, const LaneInfo &v);
void from_json(const nlohmann::json &j, LaneInfo &v);

struct RoadInfo {
  std::string id;
  Vector3 begin_pos;
  Vector3 end_pos;
  DrivingType driving_type = DrivingType::MOTOR_VEHICLE_ALLOWED;
  TrafficSignType traffic_sign_type = TrafficSignType::NO_SIGN;
  std::vector<Vector2> stop_line;
  std::vector<std::string> predecessor_ids;
  std::vector<std::string> successor_ids;
  std::vector<LaneInfo> lanes;
};

void to_json(nlohmann::json &j, const RoadInfo &v);
void from_json(const nlohmann::json &j, RoadInfo &v);

struct SceneStaticData {
  std::vector<Vector3> route;
  std::vector<RoadInfo> roads;
  std::vector<SubSceneInfo> sub_scenes;
  std::optional<VLAExtension> vla_extension;
};

void to_json(nlohmann::json &j, const SceneStaticData &v);
void from_json(const nlohmann::json &j, SceneStaticData &v);

// ── Dynamic simulation models ────────────────────────────────────────────────

struct PoseGnss {
  double pos_x = 0.0;
  double pos_y = 0.0;
  double pos_z = 0.0;
  double vel_x = 0.0;
  double vel_y = 0.0;
  double vel_z = 0.0;
  double ori_x = 0.0;
  double ori_y = 0.0;
  double ori_z = 0.0;
};

void to_json(nlohmann::json &j, const PoseGnss &v);
void from_json(const nlohmann::json &j, PoseGnss &v);

struct EulerAngle {
  double ori_x = 0.0;
  double ori_y = 0.0;
  double ori_z = 0.0;
};

void to_json(nlohmann::json &j, const EulerAngle &v);
void from_json(const nlohmann::json &j, EulerAngle &v);

struct MainVehicleInfo {
  int id = 0;
  double speed = 0.0;
  GearMode gear = GearMode::NEUTRAL;
  double throttle = 0.0;
  double brake = 0.0;
  double steering = 0.0;
  double length = 0.0;
  double width = 0.0;
  double height = 0.0;
  bool left_blinker_on = false;
  bool right_blinker_on = false;
  bool hazard_lights_on = false;
  bool brake_lights_on = false;
  bool headlights_on = false;
};

void to_json(nlohmann::json &j, const MainVehicleInfo &v);
void from_json(const nlohmann::json &j, MainVehicleInfo &v);

struct CameraInfo {
  std::string id;
  Vector3 position;
  EulerAngle orientation;
  double fov = 0.0;
  std::vector<double> intrinsic_matrix;
  int image_width = 0;
  int image_height = 0;
};

void to_json(nlohmann::json &j, const CameraInfo &v);
void from_json(const nlohmann::json &j, CameraInfo &v);

struct SensorInfo {
  std::vector<CameraInfo> ego_rgb_cams;
  std::vector<CameraInfo> v2x_cams;
};

void to_json(nlohmann::json &j, const SensorInfo &v);
void from_json(const nlohmann::json &j, SensorInfo &v);

struct ObstacleInfo {
  int id = 0;
  ObstacleType type = ObstacleType::UNKNOWN;
  double pos_x = 0.0;
  double pos_y = 0.0;
  double pos_z = 0.0;
  double vel_x = 0.0;
  double vel_y = 0.0;
  double vel_z = 0.0;
  double ori_x = 0.0;
  double ori_y = 0.0;
  double ori_z = 0.0;
  double length = 0.0;
  double width = 0.0;
  double height = 0.0;
  std::optional<std::string> extra_info;
};

void to_json(nlohmann::json &j, const ObstacleInfo &v);
void from_json(const nlohmann::json &j, ObstacleInfo &v);

struct TrafficLightInfo {
  std::string id;
  std::string road_id;
  Vector3 position;
  TrafficLightState left_state = TrafficLightState::RED;
  double left_remaining_time = 0.0;
  TrafficLightState right_state = TrafficLightState::RED;
  double right_remaining_time = 0.0;
  TrafficLightState straight_state = TrafficLightState::RED;
  double straight_remaining_time = 0.0;
};

void to_json(nlohmann::json &j, const TrafficLightInfo &v);
void from_json(const nlohmann::json &j, TrafficLightInfo &v);

struct TrafficLightGroupInfo {
  std::string id;
  std::vector<TrafficLightInfo> traffic_lights;
};

void to_json(nlohmann::json &j, const TrafficLightGroupInfo &v);
void from_json(const nlohmann::json &j, TrafficLightGroupInfo &v);

struct SceneStatus {
  std::string sub_scene_name;
  double used_time = 0.0;
  double time_limit = 0.0;
  std::optional<Vector3> end_point;
};

void to_json(nlohmann::json &j, const SceneStatus &v);
void from_json(const nlohmann::json &j, SceneStatus &v);

struct SimCarMsg {
  std::vector<Vector3> trajectory;
  PoseGnss pose_gnss;
  MainVehicleInfo main_vehicle;
  SensorInfo sensor;
  std::vector<ObstacleInfo> obstacles;
  std::vector<TrafficLightGroupInfo> traffic_light_groups;
  SceneStatus scene_status;
};

void to_json(nlohmann::json &j, const SimCarMsg &v);
void from_json(const nlohmann::json &j, SimCarMsg &v);

// ── Vehicle control models ───────────────────────────────────────────────────

struct VehicleControl {
  double throttle = 0.0;
  double brake = 0.0;
  double steering = 0.0;
  GearMode gear = GearMode::DRIVE;
  bool left_blinker_on = false;
  bool right_blinker_on = false;
  bool hazard_lights_on = false;
  bool headlights_on = false;
};

void to_json(nlohmann::json &j, const VehicleControl &v);
void from_json(const nlohmann::json &j, VehicleControl &v);

// Internal DTO used for wire format
struct VehicleControlDTO {
  double throttle = 0.0;
  double brake = 0.0;
  double steering = 0.0;
  GearMode gear = GearMode::DRIVE;
  bool left_blinker_on = false;
  bool right_blinker_on = false;
  bool hazard_lights_on = false;
  bool headlights_on = false;
  int move_to_start = 0;
  int move_to_end = 0;

  static VehicleControlDTO from_control(const VehicleControl &vc, int move_to_start,
                                        int move_to_end);
};

void to_json(nlohmann::json &j, const VehicleControlDTO &v);
void from_json(const nlohmann::json &j, VehicleControlDTO &v);

// Internal output wrapper
struct SimCarMsgOutput {
  VehicleControlDTO vehicle_control;
  std::optional<VLAExtensionOutput> vla_extension;
};

void to_json(nlohmann::json &j, const SimCarMsgOutput &v);
void from_json(const nlohmann::json &j, SimCarMsgOutput &v);

// ── Protocol messages ────────────────────────────────────────────────────────

struct Code1 {
  int code = 1;
  MapConfig map_info;
  std::optional<VLAExtension> vla_extension;
};

void to_json(nlohmann::json &j, const Code1 &v);
void from_json(const nlohmann::json &j, Code1 &v);

struct Code2 {
  int code = 2;
};

void to_json(nlohmann::json &j, const Code2 &v);
void from_json(const nlohmann::json &j, Code2 &v);

struct Code3 {
  int code = 3;
  SimCarMsg sim_car_msg;
};

void to_json(nlohmann::json &j, const Code3 &v);
void from_json(const nlohmann::json &j, Code3 &v);

struct Code4 {
  int code = 4;
  SimCarMsgOutput sim_car_msg;
};

void to_json(nlohmann::json &j, const Code4 &v);
void from_json(const nlohmann::json &j, Code4 &v);

struct Code5 {
  int code = 5;
};

void to_json(nlohmann::json &j, const Code5 &v);
void from_json(const nlohmann::json &j, Code5 &v);

} // namespace metacar

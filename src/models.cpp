#include "metacar/models.hpp"

namespace metacar {

// Helper for optional fields: only check alias key
template <typename T>
static void get_optional(const nlohmann::json &j, const std::string &key, std::optional<T> &out) {
  if (j.contains(key) && !j[key].is_null())
    out = j[key].get<T>();
  else
    out = std::nullopt;
}

// ── BuildingInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const BuildingInfo &v) {
  j = nlohmann::json{
      {"id", v.id},         {"displayName", v.name}, {"posX", v.pos_x},    {"posY", v.pos_y},
      {"posZ", v.pos_z},    {"oriX", v.ori_x},       {"oriY", v.ori_y},    {"oriZ", v.ori_z},
      {"length", v.length}, {"width", v.width},      {"height", v.height},
  };
}

void from_json(const nlohmann::json &j, BuildingInfo &v) {
  j.at("id").get_to(v.id);
  j.at("displayName").get_to(v.name);
  j.at("posX").get_to(v.pos_x);
  j.at("posY").get_to(v.pos_y);
  j.at("posZ").get_to(v.pos_z);
  j.at("oriX").get_to(v.ori_x);
  j.at("oriY").get_to(v.ori_y);
  j.at("oriZ").get_to(v.ori_z);
  j.at("length").get_to(v.length);
  j.at("width").get_to(v.width);
  j.at("height").get_to(v.height);
}

// ── RegionInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const RegionInfo &v) {
  j = nlohmann::json{
      {"id", v.id},         {"type", v.type},   {"posX", v.pos_x}, {"posY", v.pos_y},
      {"posZ", v.pos_z},    {"oriX", v.ori_x},  {"oriY", v.ori_y}, {"oriZ", v.ori_z},
      {"length", v.length}, {"width", v.width},
  };
}

void from_json(const nlohmann::json &j, RegionInfo &v) {
  j.at("id").get_to(v.id);
  j.at("type").get_to(v.type);
  j.at("posX").get_to(v.pos_x);
  j.at("posY").get_to(v.pos_y);
  j.at("posZ").get_to(v.pos_z);
  j.at("oriX").get_to(v.ori_x);
  j.at("oriY").get_to(v.ori_y);
  j.at("oriZ").get_to(v.ori_z);
  j.at("length").get_to(v.length);
  j.at("width").get_to(v.width);
}

// ── VLAExtension ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const VLAExtension &v) {
  j = nlohmann::json{
      {"BuildingInfos", v.buildings},
      {"Regions", v.regions},
  };
}

void from_json(const nlohmann::json &j, VLAExtension &v) {
  j.at("BuildingInfos").get_to(v.buildings);
  j.at("Regions").get_to(v.regions);
}

// ── VLATextOutput ────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const VLATextOutput &v) {
  j = nlohmann::json{
      {"OcrText", v.ocr_text},
      {"TimeText", v.time_phrase},
      {"LocationText", v.location_phrase},
      {"ActionText", v.action_phrase},
  };
}

void from_json(const nlohmann::json &j, VLATextOutput &v) {
  j.at("OcrText").get_to(v.ocr_text);
  j.at("TimeText").get_to(v.time_phrase);
  j.at("LocationText").get_to(v.location_phrase);
  j.at("ActionText").get_to(v.action_phrase);
}

// ── FunctionZoneViolation ────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const FunctionZoneViolation &v) {
  j = nlohmann::json{
      {"ruleCode", v.rule_code},
      {"stickerIds", v.sticker_ids},
  };
}

void from_json(const nlohmann::json &j, FunctionZoneViolation &v) {
  j.at("ruleCode").get_to(v.rule_code);
  j.at("stickerIds").get_to(v.sticker_ids);
}

// ── ParkingResult ────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const ParkingResult &v) {
  j = nlohmann::json{{"violatingStickerIds", v.violating_sticker_ids}};
}

void from_json(const nlohmann::json &j, ParkingResult &v) {
  j.at("violatingStickerIds").get_to(v.violating_sticker_ids);
}

// ── VLAExtensionOutput ───────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const VLAExtensionOutput &v) {
  j = nlohmann::json{};
  if (v.text_info)
    j["TextInfo"] = *v.text_info;
  else
    j["TextInfo"] = nullptr;
  if (v.function_zone_result)
    j["FunctionZoneResult"] = *v.function_zone_result;
  else
    j["FunctionZoneResult"] = nullptr;
  if (v.parking_result)
    j["ParkingResult"] = *v.parking_result;
  else
    j["ParkingResult"] = nullptr;
}

void from_json(const nlohmann::json &j, VLAExtensionOutput &v) {
  get_optional(j, "TextInfo", v.text_info);
  get_optional(j, "FunctionZoneResult", v.function_zone_result);
  get_optional(j, "ParkingResult", v.parking_result);
}

// ── SubSceneInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SubSceneInfo &v) {
  j = nlohmann::json{{"SubSceneName", v.name}};
  if (v.start_point)
    j["StartPoint"] = *v.start_point;
  else
    j["StartPoint"] = nullptr;
  if (v.end_point)
    j["EndPoint"] = *v.end_point;
  else
    j["EndPoint"] = nullptr;
}

void from_json(const nlohmann::json &j, SubSceneInfo &v) {
  j.at("SubSceneName").get_to(v.name);
  get_optional(j, "StartPoint", v.start_point);
  get_optional(j, "EndPoint", v.end_point);
}

// ── MapConfig ────────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const MapConfig &v) {
  j = nlohmann::json{
      {"path", v.path},
      {"route", v.route},
      {"map", v.map},
      {"SubSceneInfo", v.sub_scenes},
  };
}

void from_json(const nlohmann::json &j, MapConfig &v) {
  j.at("path").get_to(v.path);
  j.at("route").get_to(v.route);
  j.at("map").get_to(v.map);
  j.at("SubSceneInfo").get_to(v.sub_scenes);
}

// ── BorderInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const BorderInfo &v) {
  j = nlohmann::json{
      {"borderType", v.type},
      {"pathPoint", v.path_points},
  };
}

void from_json(const nlohmann::json &j, BorderInfo &v) {
  j.at("borderType").get_to(v.type);
  j.at("pathPoint").get_to(v.path_points);
}

// ── LaneInfo ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const LaneInfo &v) {
  j = nlohmann::json{
      {"id", v.id},
      {"LeftBorder", v.left_border},
      {"RightBorder", v.right_border},
      {"leftLane", v.left_lane_id},
      {"rightLane", v.right_lane_id},
      {"width", v.width},
      {"pathPoint", v.path_points},
  };
}

void from_json(const nlohmann::json &j, LaneInfo &v) {
  j.at("id").get_to(v.id);
  j.at("LeftBorder").get_to(v.left_border);
  j.at("RightBorder").get_to(v.right_border);
  j.at("leftLane").get_to(v.left_lane_id);
  j.at("rightLane").get_to(v.right_lane_id);
  j.at("width").get_to(v.width);
  j.at("pathPoint").get_to(v.path_points);
}

// ── RoadInfo ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const RoadInfo &v) {
  j = nlohmann::json{
      {"id", v.id},
      {"beginPos", v.begin_pos},
      {"endPos", v.end_pos},
      {"drivingType", v.driving_type},
      {"trafficSign", v.traffic_sign_type},
      {"stopLine", v.stop_line},
      {"predecessor", v.predecessor_ids},
      {"successor", v.successor_ids},
      {"laneData", v.lanes},
  };
}

void from_json(const nlohmann::json &j, RoadInfo &v) {
  j.at("id").get_to(v.id);
  j.at("beginPos").get_to(v.begin_pos);
  j.at("endPos").get_to(v.end_pos);
  j.at("drivingType").get_to(v.driving_type);
  j.at("trafficSign").get_to(v.traffic_sign_type);
  j.at("stopLine").get_to(v.stop_line);
  j.at("predecessor").get_to(v.predecessor_ids);
  j.at("successor").get_to(v.successor_ids);
  j.at("laneData").get_to(v.lanes);
}

// ── SceneStaticData ──────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SceneStaticData &v) {
  j = nlohmann::json{
      {"route", v.route},
      {"roads", v.roads},
      {"sub_scenes", v.sub_scenes},
  };
  if (v.vla_extension)
    j["vla_extension"] = *v.vla_extension;
  else
    j["vla_extension"] = nullptr;
}

void from_json(const nlohmann::json &j, SceneStaticData &v) {
  j.at("route").get_to(v.route);
  j.at("roads").get_to(v.roads);
  j.at("sub_scenes").get_to(v.sub_scenes);
  get_optional(j, "vla_extension", v.vla_extension);
}

// ── PoseGnss ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const PoseGnss &v) {
  j = nlohmann::json{
      {"posX", v.pos_x}, {"posY", v.pos_y}, {"posZ", v.pos_z}, {"velX", v.vel_x}, {"velY", v.vel_y},
      {"velZ", v.vel_z}, {"oriX", v.ori_x}, {"oriY", v.ori_y}, {"oriZ", v.ori_z},
  };
}

void from_json(const nlohmann::json &j, PoseGnss &v) {
  j.at("posX").get_to(v.pos_x);
  j.at("posY").get_to(v.pos_y);
  j.at("posZ").get_to(v.pos_z);
  j.at("velX").get_to(v.vel_x);
  j.at("velY").get_to(v.vel_y);
  j.at("velZ").get_to(v.vel_z);
  j.at("oriX").get_to(v.ori_x);
  j.at("oriY").get_to(v.ori_y);
  j.at("oriZ").get_to(v.ori_z);
}

// ── EulerAngle ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const EulerAngle &v) {
  j = nlohmann::json{
      {"orix", v.ori_x},
      {"oriy", v.ori_y},
      {"oriz", v.ori_z},
  };
}

void from_json(const nlohmann::json &j, EulerAngle &v) {
  j.at("orix").get_to(v.ori_x);
  j.at("oriy").get_to(v.ori_y);
  j.at("oriz").get_to(v.ori_z);
}

// ── MainVehicleInfo ──────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const MainVehicleInfo &v) {
  j = nlohmann::json{
      {"mainVehicleId", v.id},
      {"speed", v.speed},
      {"gear", v.gear},
      {"throttle", v.throttle},
      {"brake", v.brake},
      {"steering", v.steering},
      {"length", v.length},
      {"width", v.width},
      {"height", v.height},
      {"Signal_Light_LeftBlinker", v.left_blinker_on},
      {"Signal_Light_RightBlinker", v.right_blinker_on},
      {"Signal_Light_DoubleFlash", v.hazard_lights_on},
      {"Signal_Light_BrakeLight", v.brake_lights_on},
      {"Signal_Light_FrontLight", v.headlights_on},
  };
}

void from_json(const nlohmann::json &j, MainVehicleInfo &v) {
  j.at("mainVehicleId").get_to(v.id);
  j.at("speed").get_to(v.speed);
  j.at("gear").get_to(v.gear);
  j.at("throttle").get_to(v.throttle);
  j.at("brake").get_to(v.brake);
  j.at("steering").get_to(v.steering);
  j.at("length").get_to(v.length);
  j.at("width").get_to(v.width);
  j.at("height").get_to(v.height);
  j.at("Signal_Light_LeftBlinker").get_to(v.left_blinker_on);
  j.at("Signal_Light_RightBlinker").get_to(v.right_blinker_on);
  j.at("Signal_Light_DoubleFlash").get_to(v.hazard_lights_on);
  j.at("Signal_Light_BrakeLight").get_to(v.brake_lights_on);
  j.at("Signal_Light_FrontLight").get_to(v.headlights_on);
}

// ── CameraInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const CameraInfo &v) {
  j = nlohmann::json{
      {"Id", v.id},
      {"Position", v.position},
      {"Angle", v.orientation},
      {"Fov", v.fov},
      {"IntrinsicMatrix", v.intrinsic_matrix},
      {"ImageW", v.image_width},
      {"ImageH", v.image_height},
  };
}

void from_json(const nlohmann::json &j, CameraInfo &v) {
  j.at("Id").get_to(v.id);
  j.at("Position").get_to(v.position);
  j.at("Angle").get_to(v.orientation);
  j.at("Fov").get_to(v.fov);
  j.at("IntrinsicMatrix").get_to(v.intrinsic_matrix);
  j.at("ImageW").get_to(v.image_width);
  j.at("ImageH").get_to(v.image_height);
}

// ── SensorInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SensorInfo &v) {
  j = nlohmann::json{
      {"egoRGBCams", v.ego_rgb_cams},
      {"v2xCams", v.v2x_cams},
  };
}

void from_json(const nlohmann::json &j, SensorInfo &v) {
  j.at("egoRGBCams").get_to(v.ego_rgb_cams);
  j.at("v2xCams").get_to(v.v2x_cams);
}

// ── ObstacleInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const ObstacleInfo &v) {
  j = nlohmann::json{
      {"id", v.id},       {"type", v.type},     {"posX", v.pos_x}, {"posY", v.pos_y},
      {"posZ", v.pos_z},  {"velX", v.vel_x},    {"velY", v.vel_y}, {"velZ", v.vel_z},
      {"oriX", v.ori_x},  {"oriY", v.ori_y},    {"oriZ", v.ori_z}, {"length", v.length},
      {"width", v.width}, {"height", v.height},
  };
  if (v.extra_info)
    j["RedundantValue"] = *v.extra_info;
  else
    j["RedundantValue"] = nullptr;
}

void from_json(const nlohmann::json &j, ObstacleInfo &v) {
  j.at("id").get_to(v.id);
  j.at("type").get_to(v.type);
  j.at("posX").get_to(v.pos_x);
  j.at("posY").get_to(v.pos_y);
  j.at("posZ").get_to(v.pos_z);
  j.at("velX").get_to(v.vel_x);
  j.at("velY").get_to(v.vel_y);
  j.at("velZ").get_to(v.vel_z);
  j.at("oriX").get_to(v.ori_x);
  j.at("oriY").get_to(v.ori_y);
  j.at("oriZ").get_to(v.ori_z);
  j.at("length").get_to(v.length);
  j.at("width").get_to(v.width);
  j.at("height").get_to(v.height);
  get_optional(j, "RedundantValue", v.extra_info);
}

// ── TrafficLightInfo ─────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const TrafficLightInfo &v) {
  j = nlohmann::json{
      {"id", v.id},
      {"roadId", v.road_id},
      {"Position", v.position},
      {"turnLeftState", v.left_state},
      {"turnLeftRemainder", v.left_remaining_time},
      {"turnRightState", v.right_state},
      {"turnRightRemainder", v.right_remaining_time},
      {"straightState", v.straight_state},
      {"straightRemainder", v.straight_remaining_time},
  };
}

void from_json(const nlohmann::json &j, TrafficLightInfo &v) {
  j.at("id").get_to(v.id);
  j.at("roadId").get_to(v.road_id);
  j.at("Position").get_to(v.position);
  j.at("turnLeftState").get_to(v.left_state);
  j.at("turnLeftRemainder").get_to(v.left_remaining_time);
  j.at("turnRightState").get_to(v.right_state);
  j.at("turnRightRemainder").get_to(v.right_remaining_time);
  j.at("straightState").get_to(v.straight_state);
  j.at("straightRemainder").get_to(v.straight_remaining_time);
}

// ── TrafficLightGroupInfo ────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const TrafficLightGroupInfo &v) {
  j = nlohmann::json{
      {"id", v.id},
      {"trafficLightState", v.traffic_lights},
  };
}

void from_json(const nlohmann::json &j, TrafficLightGroupInfo &v) {
  j.at("id").get_to(v.id);
  j.at("trafficLightState").get_to(v.traffic_lights);
}

// ── SceneStatus ──────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SceneStatus &v) {
  j = nlohmann::json{
      {"SubSceneName", v.sub_scene_name},
      {"UsedTime", v.used_time},
      {"TimeLimit", v.time_limit},
  };
  if (v.end_point)
    j["EndPoint"] = *v.end_point;
  else
    j["EndPoint"] = nullptr;
}

void from_json(const nlohmann::json &j, SceneStatus &v) {
  j.at("SubSceneName").get_to(v.sub_scene_name);
  j.at("UsedTime").get_to(v.used_time);
  j.at("TimeLimit").get_to(v.time_limit);
  get_optional(j, "EndPoint", v.end_point);
}

// ── SimCarMsg ────────────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SimCarMsg &v) {
  j = nlohmann::json{
      {"Trajectory", v.trajectory},        {"PoseGnss", v.pose_gnss},
      {"DataMainVehicle", v.main_vehicle}, {"Sensor", v.sensor},
      {"ObstacleEntryList", v.obstacles},  {"TrafficLightStateLists", v.traffic_light_groups},
      {"SceneStatus", v.scene_status},
  };
}

void from_json(const nlohmann::json &j, SimCarMsg &v) {
  j.at("Trajectory").get_to(v.trajectory);
  j.at("PoseGnss").get_to(v.pose_gnss);
  j.at("DataMainVehicle").get_to(v.main_vehicle);
  j.at("Sensor").get_to(v.sensor);
  j.at("ObstacleEntryList").get_to(v.obstacles);
  j.at("TrafficLightStateLists").get_to(v.traffic_light_groups);
  j.at("SceneStatus").get_to(v.scene_status);
}

// ── VehicleControlDTO ────────────────────────────────────────────────────────

VehicleControlDTO VehicleControlDTO::from_control(const VehicleControl &vc, int mts, int mte) {
  VehicleControlDTO dto;
  dto.throttle = vc.throttle;
  dto.brake = vc.brake;
  dto.steering = vc.steering;
  dto.gear = vc.gear;
  dto.left_blinker_on = vc.left_blinker_on;
  dto.right_blinker_on = vc.right_blinker_on;
  dto.hazard_lights_on = vc.hazard_lights_on;
  dto.headlights_on = vc.headlights_on;
  dto.move_to_start = mts;
  dto.move_to_end = mte;
  return dto;
}

void to_json(nlohmann::json &j, const VehicleControlDTO &v) {
  j = nlohmann::json{
      {"throttle", v.throttle},
      {"brake", v.brake},
      {"steering", v.steering},
      {"gear", v.gear},
      {"Signal_Light_LeftBlinker", v.left_blinker_on},
      {"Signal_Light_RightBlinker", v.right_blinker_on},
      {"Signal_Light_DoubleFlash", v.hazard_lights_on},
      {"Signal_Light_FrontLight", v.headlights_on},
      {"movetostart", v.move_to_start},
      {"movetoend", v.move_to_end},
  };
}

void from_json(const nlohmann::json &j, VehicleControlDTO &v) {
  j.at("throttle").get_to(v.throttle);
  j.at("brake").get_to(v.brake);
  j.at("steering").get_to(v.steering);
  j.at("gear").get_to(v.gear);
  j.at("Signal_Light_LeftBlinker").get_to(v.left_blinker_on);
  j.at("Signal_Light_RightBlinker").get_to(v.right_blinker_on);
  j.at("Signal_Light_DoubleFlash").get_to(v.hazard_lights_on);
  j.at("Signal_Light_FrontLight").get_to(v.headlights_on);
  j.at("movetostart").get_to(v.move_to_start);
  j.at("movetoend").get_to(v.move_to_end);
}

// ── SimCarMsgOutput ──────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const SimCarMsgOutput &v) {
  j = nlohmann::json{
      {"VehicleControl", v.vehicle_control},
  };
  if (v.vla_extension)
    j["VLAExtension"] = *v.vla_extension;
  else
    j["VLAExtension"] = nullptr;
}

void from_json(const nlohmann::json &j, SimCarMsgOutput &v) {
  j.at("VehicleControl").get_to(v.vehicle_control);
  get_optional(j, "VLAExtension", v.vla_extension);
}

// ── Protocol messages ────────────────────────────────────────────────────────

void to_json(nlohmann::json &j, const Code1 &v) {
  j = nlohmann::json{
      {"code", v.code},
      {"MapInfo", v.map_info},
  };
  if (v.vla_extension)
    j["VLAExtension"] = *v.vla_extension;
  else
    j["VLAExtension"] = nullptr;
}

void from_json(const nlohmann::json &j, Code1 &v) {
  j.at("code").get_to(v.code);
  j.at("MapInfo").get_to(v.map_info);
  get_optional(j, "VLAExtension", v.vla_extension);
}

void to_json(nlohmann::json &j, const Code3 &v) {
  j = nlohmann::json{
      {"code", v.code},
      {"SimCarMsg", v.sim_car_msg},
  };
}

void from_json(const nlohmann::json &j, Code3 &v) {
  j.at("code").get_to(v.code);
  j.at("SimCarMsg").get_to(v.sim_car_msg);
}

void to_json(nlohmann::json &j, const Code4 &v) {
  j = nlohmann::json{
      {"code", v.code},
      {"SimCarMsg", v.sim_car_msg},
  };
}

void from_json(const nlohmann::json &j, Code4 &v) {
  j.at("code").get_to(v.code);
  j.at("SimCarMsg").get_to(v.sim_car_msg);
}

} // namespace metacar

#include "metacar/models.hpp"

namespace metacar {

// Helper: get value from json, trying alias first then field name
template <typename T>
static void get_field(const nlohmann::json& j, const std::string& alias, const std::string& field, T& out) {
    if (j.contains(alias)) {
        j.at(alias).get_to(out);
    } else if (j.contains(field)) {
        j.at(field).get_to(out);
    }
}

// Helper for optional fields
template <typename T>
static void get_optional_field(const nlohmann::json& j, const std::string& alias, const std::string& field, std::optional<T>& out) {
    if (j.contains(alias) && !j.at(alias).is_null()) {
        out = j.at(alias).get<T>();
    } else if (j.contains(field) && !j.at(field).is_null()) {
        out = j.at(field).get<T>();
    } else {
        out = std::nullopt;
    }
}

// ── BuildingInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const BuildingInfo& v) {
    j = nlohmann::json{
        {"id", v.id},
        {"displayName", v.name},
        {"posX", v.pos_x}, {"posY", v.pos_y}, {"posZ", v.pos_z},
        {"oriX", v.ori_x}, {"oriY", v.ori_y}, {"oriZ", v.ori_z},
        {"length", v.length}, {"width", v.width}, {"height", v.height},
    };
}

void from_json(const nlohmann::json& j, BuildingInfo& v) {
    j.at("id").get_to(v.id);
    get_field(j, "displayName", "name", v.name);
    get_field(j, "posX", "pos_x", v.pos_x);
    get_field(j, "posY", "pos_y", v.pos_y);
    get_field(j, "posZ", "pos_z", v.pos_z);
    get_field(j, "oriX", "ori_x", v.ori_x);
    get_field(j, "oriY", "ori_y", v.ori_y);
    get_field(j, "oriZ", "ori_z", v.ori_z);
    j.at("length").get_to(v.length);
    j.at("width").get_to(v.width);
    j.at("height").get_to(v.height);
}

// ── RegionInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const RegionInfo& v) {
    j = nlohmann::json{
        {"id", v.id}, {"type", v.type},
        {"posX", v.pos_x}, {"posY", v.pos_y}, {"posZ", v.pos_z},
        {"oriX", v.ori_x}, {"oriY", v.ori_y}, {"oriZ", v.ori_z},
        {"length", v.length}, {"width", v.width},
    };
}

void from_json(const nlohmann::json& j, RegionInfo& v) {
    j.at("id").get_to(v.id);
    j.at("type").get_to(v.type);
    get_field(j, "posX", "pos_x", v.pos_x);
    get_field(j, "posY", "pos_y", v.pos_y);
    get_field(j, "posZ", "pos_z", v.pos_z);
    get_field(j, "oriX", "ori_x", v.ori_x);
    get_field(j, "oriY", "ori_y", v.ori_y);
    get_field(j, "oriZ", "ori_z", v.ori_z);
    j.at("length").get_to(v.length);
    j.at("width").get_to(v.width);
}

// ── VLAExtension ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const VLAExtension& v) {
    j = nlohmann::json{
        {"BuildingInfos", v.buildings},
        {"Regions", v.regions},
    };
}

void from_json(const nlohmann::json& j, VLAExtension& v) {
    get_field(j, "BuildingInfos", "buildings", v.buildings);
    get_field(j, "Regions", "regions", v.regions);
}

// ── VLATextOutput ────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const VLATextOutput& v) {
    j = nlohmann::json{
        {"OcrText", v.ocr_text},
        {"TimeText", v.time_phrase},
        {"LocationText", v.location_phrase},
        {"ActionText", v.action_phrase},
    };
}

void from_json(const nlohmann::json& j, VLATextOutput& v) {
    get_field(j, "OcrText", "ocr_text", v.ocr_text);
    get_field(j, "TimeText", "time_phrase", v.time_phrase);
    get_field(j, "LocationText", "location_phrase", v.location_phrase);
    get_field(j, "ActionText", "action_phrase", v.action_phrase);
}

// ── FunctionZoneViolation ────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const FunctionZoneViolation& v) {
    j = nlohmann::json{
        {"ruleCode", v.rule_code},
        {"stickerIds", v.sticker_ids},
    };
}

void from_json(const nlohmann::json& j, FunctionZoneViolation& v) {
    get_field(j, "ruleCode", "rule_code", v.rule_code);
    get_field(j, "stickerIds", "sticker_ids", v.sticker_ids);
}

// ── FunctionZoneResult ───────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const FunctionZoneResult& v) {
    j = nlohmann::json{{"violations", v.violations}};
}

void from_json(const nlohmann::json& j, FunctionZoneResult& v) {
    j.at("violations").get_to(v.violations);
}

// ── ParkingResult ────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const ParkingResult& v) {
    j = nlohmann::json{{"violatingStickerIds", v.violating_sticker_ids}};
}

void from_json(const nlohmann::json& j, ParkingResult& v) {
    get_field(j, "violatingStickerIds", "violating_sticker_ids", v.violating_sticker_ids);
}

// ── VLAExtensionOutput ───────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const VLAExtensionOutput& v) {
    j = nlohmann::json{};
    if (v.text_info) {
        j["TextInfo"] = *v.text_info;
    } else {
        j["TextInfo"] = nullptr;
    }
    if (v.function_zone_result) {
        j["FunctionZoneResult"] = *v.function_zone_result;
    } else {
        j["FunctionZoneResult"] = nullptr;
    }
    if (v.parking_result) {
        j["ParkingResult"] = *v.parking_result;
    } else {
        j["ParkingResult"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, VLAExtensionOutput& v) {
    get_optional_field(j, "TextInfo", "text_info", v.text_info);
    get_optional_field(j, "FunctionZoneResult", "function_zone_result", v.function_zone_result);
    get_optional_field(j, "ParkingResult", "parking_result", v.parking_result);
}

// ── SubSceneInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SubSceneInfo& v) {
    j = nlohmann::json{{"SubSceneName", v.name}};
    if (v.start_point) {
        j["StartPoint"] = *v.start_point;
    } else {
        j["StartPoint"] = nullptr;
    }
    if (v.end_point) {
        j["EndPoint"] = *v.end_point;
    } else {
        j["EndPoint"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, SubSceneInfo& v) {
    get_field(j, "SubSceneName", "name", v.name);
    get_optional_field(j, "StartPoint", "start_point", v.start_point);
    get_optional_field(j, "EndPoint", "end_point", v.end_point);
}

// ── MapConfig ────────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const MapConfig& v) {
    j = nlohmann::json{
        {"path", v.path},
        {"route", v.route},
        {"map", v.map},
        {"SubSceneInfo", v.sub_scenes},
    };
}

void from_json(const nlohmann::json& j, MapConfig& v) {
    j.at("path").get_to(v.path);
    j.at("route").get_to(v.route);
    j.at("map").get_to(v.map);
    get_field(j, "SubSceneInfo", "sub_scenes", v.sub_scenes);
}

// ── BorderInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const BorderInfo& v) {
    j = nlohmann::json{
        {"borderType", v.type},
        {"pathPoint", v.path_points},
    };
}

void from_json(const nlohmann::json& j, BorderInfo& v) {
    get_field(j, "borderType", "type", v.type);
    get_field(j, "pathPoint", "path_points", v.path_points);
}

// ── LaneInfo ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const LaneInfo& v) {
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

void from_json(const nlohmann::json& j, LaneInfo& v) {
    j.at("id").get_to(v.id);
    get_field(j, "LeftBorder", "left_border", v.left_border);
    get_field(j, "RightBorder", "right_border", v.right_border);
    get_field(j, "leftLane", "left_lane_id", v.left_lane_id);
    get_field(j, "rightLane", "right_lane_id", v.right_lane_id);
    j.at("width").get_to(v.width);
    get_field(j, "pathPoint", "path_points", v.path_points);
}

// ── RoadInfo ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const RoadInfo& v) {
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

void from_json(const nlohmann::json& j, RoadInfo& v) {
    j.at("id").get_to(v.id);
    get_field(j, "beginPos", "begin_pos", v.begin_pos);
    get_field(j, "endPos", "end_pos", v.end_pos);
    get_field(j, "drivingType", "driving_type", v.driving_type);
    get_field(j, "trafficSign", "traffic_sign_type", v.traffic_sign_type);
    get_field(j, "stopLine", "stop_line", v.stop_line);
    get_field(j, "predecessor", "predecessor_ids", v.predecessor_ids);
    get_field(j, "successor", "successor_ids", v.successor_ids);
    get_field(j, "laneData", "lanes", v.lanes);
}

// ── SceneStaticData ──────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SceneStaticData& v) {
    j = nlohmann::json{
        {"route", v.route},
        {"roads", v.roads},
        {"sub_scenes", v.sub_scenes},
    };
    if (v.vla_extension) {
        j["vla_extension"] = *v.vla_extension;
    } else {
        j["vla_extension"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, SceneStaticData& v) {
    j.at("route").get_to(v.route);
    j.at("roads").get_to(v.roads);
    j.at("sub_scenes").get_to(v.sub_scenes);
    get_optional_field(j, "vla_extension", "vla_extension", v.vla_extension);
}

// ── PoseGnss ─────────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const PoseGnss& v) {
    j = nlohmann::json{
        {"posX", v.pos_x}, {"posY", v.pos_y}, {"posZ", v.pos_z},
        {"velX", v.vel_x}, {"velY", v.vel_y}, {"velZ", v.vel_z},
        {"oriX", v.ori_x}, {"oriY", v.ori_y}, {"oriZ", v.ori_z},
    };
}

void from_json(const nlohmann::json& j, PoseGnss& v) {
    get_field(j, "posX", "pos_x", v.pos_x);
    get_field(j, "posY", "pos_y", v.pos_y);
    get_field(j, "posZ", "pos_z", v.pos_z);
    get_field(j, "velX", "vel_x", v.vel_x);
    get_field(j, "velY", "vel_y", v.vel_y);
    get_field(j, "velZ", "vel_z", v.vel_z);
    get_field(j, "oriX", "ori_x", v.ori_x);
    get_field(j, "oriY", "ori_y", v.ori_y);
    get_field(j, "oriZ", "ori_z", v.ori_z);
}

// ── EulerAngle ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const EulerAngle& v) {
    // Python uses lowercase "orix", "oriy", "oriz" for compatibility
    j = nlohmann::json{
        {"orix", v.ori_x}, {"oriy", v.ori_y}, {"oriz", v.ori_z},
    };
}

void from_json(const nlohmann::json& j, EulerAngle& v) {
    get_field(j, "orix", "ori_x", v.ori_x);
    get_field(j, "oriy", "ori_y", v.ori_y);
    get_field(j, "oriz", "ori_z", v.ori_z);
}

// ── MainVehicleInfo ──────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const MainVehicleInfo& v) {
    j = nlohmann::json{
        {"mainVehicleId", v.id},
        {"speed", v.speed}, {"gear", v.gear},
        {"throttle", v.throttle}, {"brake", v.brake}, {"steering", v.steering},
        {"length", v.length}, {"width", v.width}, {"height", v.height},
        {"Signal_Light_LeftBlinker", v.left_blinker_on},
        {"Signal_Light_RightBlinker", v.right_blinker_on},
        {"Signal_Light_DoubleFlash", v.hazard_lights_on},
        {"Signal_Light_BrakeLight", v.brake_lights_on},
        {"Signal_Light_FrontLight", v.headlights_on},
    };
}

void from_json(const nlohmann::json& j, MainVehicleInfo& v) {
    get_field(j, "mainVehicleId", "id", v.id);
    j.at("speed").get_to(v.speed);
    j.at("gear").get_to(v.gear);
    j.at("throttle").get_to(v.throttle);
    j.at("brake").get_to(v.brake);
    j.at("steering").get_to(v.steering);
    j.at("length").get_to(v.length);
    j.at("width").get_to(v.width);
    j.at("height").get_to(v.height);
    get_field(j, "Signal_Light_LeftBlinker", "left_blinker_on", v.left_blinker_on);
    get_field(j, "Signal_Light_RightBlinker", "right_blinker_on", v.right_blinker_on);
    get_field(j, "Signal_Light_DoubleFlash", "hazard_lights_on", v.hazard_lights_on);
    get_field(j, "Signal_Light_BrakeLight", "brake_lights_on", v.brake_lights_on);
    get_field(j, "Signal_Light_FrontLight", "headlights_on", v.headlights_on);
}

// ── CameraInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const CameraInfo& v) {
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

void from_json(const nlohmann::json& j, CameraInfo& v) {
    get_field(j, "Id", "id", v.id);
    get_field(j, "Position", "position", v.position);
    get_field(j, "Angle", "orientation", v.orientation);
    get_field(j, "Fov", "fov", v.fov);
    get_field(j, "IntrinsicMatrix", "intrinsic_matrix", v.intrinsic_matrix);
    get_field(j, "ImageW", "image_width", v.image_width);
    get_field(j, "ImageH", "image_height", v.image_height);
}

// ── SensorInfo ───────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SensorInfo& v) {
    j = nlohmann::json{
        {"egoRGBCams", v.ego_rgb_cams},
        {"v2xCams", v.v2x_cams},
    };
}

void from_json(const nlohmann::json& j, SensorInfo& v) {
    get_field(j, "egoRGBCams", "ego_rgb_cams", v.ego_rgb_cams);
    get_field(j, "v2xCams", "v2x_cams", v.v2x_cams);
}

// ── ObstacleInfo ─────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const ObstacleInfo& v) {
    j = nlohmann::json{
        {"id", v.id}, {"type", v.type},
        {"posX", v.pos_x}, {"posY", v.pos_y}, {"posZ", v.pos_z},
        {"velX", v.vel_x}, {"velY", v.vel_y}, {"velZ", v.vel_z},
        {"oriX", v.ori_x}, {"oriY", v.ori_y}, {"oriZ", v.ori_z},
        {"length", v.length}, {"width", v.width}, {"height", v.height},
    };
    if (v.extra_info) {
        j["RedundantValue"] = *v.extra_info;
    } else {
        j["RedundantValue"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, ObstacleInfo& v) {
    j.at("id").get_to(v.id);
    j.at("type").get_to(v.type);
    get_field(j, "posX", "pos_x", v.pos_x);
    get_field(j, "posY", "pos_y", v.pos_y);
    get_field(j, "posZ", "pos_z", v.pos_z);
    get_field(j, "velX", "vel_x", v.vel_x);
    get_field(j, "velY", "vel_y", v.vel_y);
    get_field(j, "velZ", "vel_z", v.vel_z);
    get_field(j, "oriX", "ori_x", v.ori_x);
    get_field(j, "oriY", "ori_y", v.ori_y);
    get_field(j, "oriZ", "ori_z", v.ori_z);
    j.at("length").get_to(v.length);
    j.at("width").get_to(v.width);
    j.at("height").get_to(v.height);
    get_optional_field(j, "RedundantValue", "extra_info", v.extra_info);
}

// ── TrafficLightInfo ─────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const TrafficLightInfo& v) {
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

void from_json(const nlohmann::json& j, TrafficLightInfo& v) {
    j.at("id").get_to(v.id);
    get_field(j, "roadId", "road_id", v.road_id);
    get_field(j, "Position", "position", v.position);
    get_field(j, "turnLeftState", "left_state", v.left_state);
    get_field(j, "turnLeftRemainder", "left_remaining_time", v.left_remaining_time);
    get_field(j, "turnRightState", "right_state", v.right_state);
    get_field(j, "turnRightRemainder", "right_remaining_time", v.right_remaining_time);
    get_field(j, "straightState", "straight_state", v.straight_state);
    get_field(j, "straightRemainder", "straight_remaining_time", v.straight_remaining_time);
}

// ── TrafficLightGroupInfo ────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const TrafficLightGroupInfo& v) {
    j = nlohmann::json{
        {"id", v.id},
        {"trafficLightState", v.traffic_lights},
    };
}

void from_json(const nlohmann::json& j, TrafficLightGroupInfo& v) {
    j.at("id").get_to(v.id);
    get_field(j, "trafficLightState", "traffic_lights", v.traffic_lights);
}

// ── SceneStatus ──────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SceneStatus& v) {
    j = nlohmann::json{
        {"SubSceneName", v.sub_scene_name},
        {"UsedTime", v.used_time},
        {"TimeLimit", v.time_limit},
    };
    if (v.end_point) {
        j["EndPoint"] = *v.end_point;
    } else {
        j["EndPoint"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, SceneStatus& v) {
    get_field(j, "SubSceneName", "sub_scene_name", v.sub_scene_name);
    get_field(j, "UsedTime", "used_time", v.used_time);
    get_field(j, "TimeLimit", "time_limit", v.time_limit);
    get_optional_field(j, "EndPoint", "end_point", v.end_point);
}

// ── SimCarMsg ────────────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SimCarMsg& v) {
    j = nlohmann::json{
        {"Trajectory", v.trajectory},
        {"PoseGnss", v.pose_gnss},
        {"DataMainVehicle", v.main_vehicle},
        {"Sensor", v.sensor},
        {"ObstacleEntryList", v.obstacles},
        {"TrafficLightStateLists", v.traffic_light_groups},
        {"SceneStatus", v.scene_status},
    };
}

void from_json(const nlohmann::json& j, SimCarMsg& v) {
    get_field(j, "Trajectory", "trajectory", v.trajectory);
    get_field(j, "PoseGnss", "pose_gnss", v.pose_gnss);
    get_field(j, "DataMainVehicle", "main_vehicle", v.main_vehicle);
    get_field(j, "Sensor", "sensor", v.sensor);
    get_field(j, "ObstacleEntryList", "obstacles", v.obstacles);
    get_field(j, "TrafficLightStateLists", "traffic_light_groups", v.traffic_light_groups);
    get_field(j, "SceneStatus", "scene_status", v.scene_status);
}

// ── VehicleControl ───────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const VehicleControl& v) {
    j = nlohmann::json{
        {"throttle", v.throttle}, {"brake", v.brake}, {"steering", v.steering},
        {"gear", v.gear},
        {"left_blinker_on", v.left_blinker_on},
        {"right_blinker_on", v.right_blinker_on},
        {"hazard_lights_on", v.hazard_lights_on},
        {"headlights_on", v.headlights_on},
    };
}

void from_json(const nlohmann::json& j, VehicleControl& v) {
    j.at("throttle").get_to(v.throttle);
    j.at("brake").get_to(v.brake);
    j.at("steering").get_to(v.steering);
    j.at("gear").get_to(v.gear);
    j.at("left_blinker_on").get_to(v.left_blinker_on);
    j.at("right_blinker_on").get_to(v.right_blinker_on);
    j.at("hazard_lights_on").get_to(v.hazard_lights_on);
    j.at("headlights_on").get_to(v.headlights_on);
}

// ── VehicleControlDTO ────────────────────────────────────────────────────────

VehicleControlDTO VehicleControlDTO::from_control(const VehicleControl& vc, int mts, int mte) {
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

void to_json(nlohmann::json& j, const VehicleControlDTO& v) {
    j = nlohmann::json{
        {"throttle", v.throttle}, {"brake", v.brake}, {"steering", v.steering},
        {"gear", v.gear},
        {"Signal_Light_LeftBlinker", v.left_blinker_on},
        {"Signal_Light_RightBlinker", v.right_blinker_on},
        {"Signal_Light_DoubleFlash", v.hazard_lights_on},
        {"Signal_Light_FrontLight", v.headlights_on},
        {"movetostart", v.move_to_start},
        {"movetoend", v.move_to_end},
    };
}

void from_json(const nlohmann::json& j, VehicleControlDTO& v) {
    j.at("throttle").get_to(v.throttle);
    j.at("brake").get_to(v.brake);
    j.at("steering").get_to(v.steering);
    j.at("gear").get_to(v.gear);
    get_field(j, "Signal_Light_LeftBlinker", "left_blinker_on", v.left_blinker_on);
    get_field(j, "Signal_Light_RightBlinker", "right_blinker_on", v.right_blinker_on);
    get_field(j, "Signal_Light_DoubleFlash", "hazard_lights_on", v.hazard_lights_on);
    get_field(j, "Signal_Light_FrontLight", "headlights_on", v.headlights_on);
    get_field(j, "movetostart", "move_to_start", v.move_to_start);
    get_field(j, "movetoend", "move_to_end", v.move_to_end);
}

// ── SimCarMsgOutput ──────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const SimCarMsgOutput& v) {
    j = nlohmann::json{
        {"VehicleControl", v.vehicle_control},
    };
    if (v.vla_extension) {
        j["VLAExtension"] = *v.vla_extension;
    } else {
        j["VLAExtension"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, SimCarMsgOutput& v) {
    get_field(j, "VehicleControl", "vehicle_control", v.vehicle_control);
    get_optional_field(j, "VLAExtension", "vla_extension", v.vla_extension);
}

// ── Protocol messages ────────────────────────────────────────────────────────

void to_json(nlohmann::json& j, const Code1& v) {
    j = nlohmann::json{
        {"code", v.code},
        {"MapInfo", v.map_info},
    };
    if (v.vla_extension) {
        j["VLAExtension"] = *v.vla_extension;
    } else {
        j["VLAExtension"] = nullptr;
    }
}

void from_json(const nlohmann::json& j, Code1& v) {
    j.at("code").get_to(v.code);
    get_field(j, "MapInfo", "map_info", v.map_info);
    get_optional_field(j, "VLAExtension", "vla_extension", v.vla_extension);
}

void to_json(nlohmann::json& j, const Code2& v) {
    j = nlohmann::json{{"code", v.code}};
}

void from_json(const nlohmann::json& j, Code2& v) {
    j.at("code").get_to(v.code);
}

void to_json(nlohmann::json& j, const Code3& v) {
    j = nlohmann::json{
        {"code", v.code},
        {"SimCarMsg", v.sim_car_msg},
    };
}

void from_json(const nlohmann::json& j, Code3& v) {
    j.at("code").get_to(v.code);
    get_field(j, "SimCarMsg", "sim_car_msg", v.sim_car_msg);
}

void to_json(nlohmann::json& j, const Code4& v) {
    j = nlohmann::json{
        {"code", v.code},
        {"SimCarMsg", v.sim_car_msg},
    };
}

void from_json(const nlohmann::json& j, Code4& v) {
    j.at("code").get_to(v.code);
    get_field(j, "SimCarMsg", "sim_car_msg", v.sim_car_msg);
}

void to_json(nlohmann::json& j, const Code5& v) {
    j = nlohmann::json{{"code", v.code}};
}

void from_json(const nlohmann::json& j, Code5& v) {
    j.at("code").get_to(v.code);
}

} // namespace metacar

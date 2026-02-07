#include "metacar/geometry.hpp"

namespace metacar {

// ── Vector2 ──────────────────────────────────────────────────────────────────

Vector2 Vector2::rotate_rad(double radians) const {
  double c = std::cos(radians);
  double s = std::sin(radians);
  return {x * c - y * s, x * s + y * c};
}

double Vector2::angle_rad() const { return std::atan2(y, x); }

double Vector2::length() const { return std::sqrt(x * x + y * y); }

Vector2 Vector2::normalized() const {
  double len = length();
  return {x / len, y / len};
}

void to_json(nlohmann::json &j, const Vector2 &v) { j = nlohmann::json{{"x", v.x}, {"y", v.y}}; }

void from_json(const nlohmann::json &j, Vector2 &v) {
  j.at("x").get_to(v.x);
  j.at("y").get_to(v.y);
}

// ── Vector3 ──────────────────────────────────────────────────────────────────

double Vector3::yaw_rad() const { return std::atan2(y, x); }

Vector2 Vector3::to_vector2() const { return {x, y}; }

double Vector3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vector3 Vector3::normalized() const {
  double len = length();
  return {x / len, y / len, z / len};
}

void to_json(nlohmann::json &j, const Vector3 &v) {
  j = nlohmann::json{{"x", v.x}, {"y", v.y}, {"z", v.z}};
}

void from_json(const nlohmann::json &j, Vector3 &v) {
  j.at("x").get_to(v.x);
  j.at("y").get_to(v.y);
  j.at("z").get_to(v.z);
}

} // namespace metacar

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

// ── Vector3 ──────────────────────────────────────────────────────────────────

double Vector3::yaw_rad() const { return std::atan2(y, x); }

Vector2 Vector3::to_vector2() const { return {x, y}; }

double Vector3::length() const { return std::sqrt(x * x + y * y + z * z); }

Vector3 Vector3::normalized() const {
  double len = length();
  return {x / len, y / len, z / len};
}

} // namespace metacar

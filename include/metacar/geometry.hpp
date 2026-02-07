#pragma once

#include <cmath>
#include <nlohmann/json.hpp>

namespace metacar {

struct Vector2 {
  double x = 0.0;
  double y = 0.0;

  Vector2() = default;
  Vector2(double x, double y) : x(x), y(y) {}

  Vector2 operator+() const { return *this; }
  Vector2 operator-() const { return {-x, -y}; }
  Vector2 operator+(const Vector2 &other) const { return {x + other.x, y + other.y}; }
  Vector2 operator-(const Vector2 &other) const { return {x - other.x, y - other.y}; }
  Vector2 operator*(double s) const { return {x * s, y * s}; }
  Vector2 operator/(double s) const { return {x / s, y / s}; }
  friend Vector2 operator*(double s, const Vector2 &v) { return v * s; }

  /// Rotate around origin (counterclockwise, radians).
  Vector2 rotate_rad(double radians) const;

  /// Angle with x-axis in [-pi, pi].
  double angle_rad() const;

  /// Euclidean length.
  double length() const;

  /// Unit vector in same direction.
  Vector2 normalized() const;
};

void to_json(nlohmann::json &j, const Vector2 &v);
void from_json(const nlohmann::json &j, Vector2 &v);

struct Vector3 {
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  Vector3() = default;
  Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

  Vector3 operator+() const { return *this; }
  Vector3 operator-() const { return {-x, -y, -z}; }
  Vector3 operator+(const Vector3 &other) const { return {x + other.x, y + other.y, z + other.z}; }
  Vector3 operator-(const Vector3 &other) const { return {x - other.x, y - other.y, z - other.z}; }
  Vector3 operator*(double s) const { return {x * s, y * s, z * s}; }
  Vector3 operator/(double s) const { return {x / s, y / s, z / s}; }
  friend Vector3 operator*(double s, const Vector3 &v) { return v * s; }

  /// Yaw angle (xOy plane projection with x-axis) in [-pi, pi].
  double yaw_rad() const;

  /// Extract x, y as Vector2.
  Vector2 to_vector2() const;

  /// Euclidean length.
  double length() const;

  /// Unit vector in same direction.
  Vector3 normalized() const;
};

void to_json(nlohmann::json &j, const Vector3 &v);
void from_json(const nlohmann::json &j, Vector3 &v);

} // namespace metacar

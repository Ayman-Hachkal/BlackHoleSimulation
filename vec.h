#pragma once

#include <raylib.h>
class vec {
  public: 
    double e[3];
    vec() : e{0, 0, 0} {}

    vec (double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double y() const { return e[1]; }
    double z() const { return e[2]; }

    vec operator-() const { return vec(-e[0], -e[1], -e[2]); }
    vec operator+(const vec& v) const { return vec(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]); } 
    vec operator-(const vec& v) const { return vec(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]); }
    vec operator*(const vec& v) const { return vec(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]); }
    vec operator*(double t) const { return vec(e[0] * t, e[1] * t, e[2] * t); }
    vec operator/(double t) const { return vec(e[0] / t, e[1] / t, e[2] / t); }
    vec operator/(const vec& v) const { return vec(e[0] / v.e[0], e[1] / v.e[1], e[2] / v.e[2]); }
};

inline double dot(const vec& u, const vec& v) {
  return ((u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]));
}
inline Vector3 toVector3(const vec& u) {
  return Vector3({static_cast<float>(u.e[0]), static_cast<float>(u.e[1]), static_cast<float>(u.e[2])});
}

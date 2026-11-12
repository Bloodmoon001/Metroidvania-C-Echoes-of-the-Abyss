#pragma once
#include <cmath>
namespace game {
    struct Vector2 {
        float x = 0.0f; float y = 0.0f;
        Vector2 operator+(const Vector2& o) const { return {x + o.x, y + o.y}; }
        Vector2 operator-(const Vector2& o) const { return {x - o.x, y - o.y}; }
        Vector2 operator*(float s) const { return {x * s, y * s}; }
        Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
        float lengthSquared() const { return x * x + y * y; }
        float length() const { return std::sqrt(lengthSquared()); }
        Vector2 normalized() const { float len = length(); if (len < 1e-6f) return {0,0}; return {x/len, y/len}; }
        static float distance(const Vector2& a, const Vector2& b) { return (b - a).length(); }
    };
}

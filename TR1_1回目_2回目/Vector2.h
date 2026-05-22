#pragma once
struct Vector2{
	float x;
	float y;

    // 加算
    Vector2 operator+(const Vector2& v) const {
        return { x + v.x, y + v.y };
    }

    // 減算 
    Vector2 operator-(const Vector2& v) const {
        return { x - v.x, y - v.y };
    }

    // 乗算 
    Vector2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    // 除算 
    Vector2 operator/(float scalar) const {
        return { x / scalar, y / scalar };
    }
};

Vector2 Normalize(const Vector2& v);

float Length(const Vector2& v);


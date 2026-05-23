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

    Vector2 operator*(const Vector2& v) {
        return { this->x * v.x,this->y * v.y };
    }

    // 除算 
    Vector2 operator/(float scalar) const {
        return { x / scalar, y / scalar };
    }
};

Vector2 Normalize(const Vector2& v);

float Length(const Vector2& v);

float Distance(const Vector2& v1, const Vector2 v2);

float Dot(const Vector2& v1, const Vector2 v2);


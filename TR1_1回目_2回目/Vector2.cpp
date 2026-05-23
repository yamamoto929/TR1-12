#include "Vector2.h"
#include <cmath>
Vector2 Normalize(const Vector2& v) {
	float length = Length(v);
	if (length == 0.0f) { return v; }
	return { v.x / length,v.y / length };
}

float Length(const Vector2& v) {
	return std::sqrt(v.x * v.x + v.y * v.y);
}

float Distance(const Vector2& v1, const Vector2 v2) {
	return Length(v1 + (v2 * -1.0f));
}

float Dot(const Vector2& v1, const Vector2 v2) {
	return { v1.x * v2.x + v1.y * v2.y };
}
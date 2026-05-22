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
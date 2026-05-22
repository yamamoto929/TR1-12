#pragma once
#include "Vector2.h"
// 多様体
struct Manifold{
	float depth; // 重なっている距離
	Vector2 normal; // 衝突法線(正規化必須)
	Vector2 contactPoint; // 衝突が発生する場所
};

void DrawManifold(const Manifold& manifold);
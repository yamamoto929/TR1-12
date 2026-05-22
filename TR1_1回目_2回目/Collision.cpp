#include "Collision.h"
#include <cmath>
bool IsCollision(Circle& c1, Circle& c2) {
	// 2つの円の中心点の差
	float distanceX = c2.GetCenter().x - c1.GetCenter().x;
	float distanceY = c2.GetCenter().y - c1.GetCenter().y;

	// 距離の2乗
	float distanceSq = (distanceX * distanceX) + (distanceY * distanceY);

	float c1Radius = c1.GetRadius();
	float c2Radius = c2.GetRadius();
	float radiusSum = c1Radius + c2Radius;

	// 衝突判定
	if (distanceSq <= radiusSum * radiusSum) {
		return true;
	}
	return false;
}

void Collide(Circle& c1, Circle& c2, Manifold& manifold) {
	// 2つの円の中心点の差
	float distanceX = c2.GetCenter().x - c1.GetCenter().x;
	float distanceY = c2.GetCenter().y - c1.GetCenter().y;

	// 距離の2乗
	float distanceSq = (distanceX * distanceX) + (distanceY * distanceY);

	float c1Radius = c1.GetRadius();
	float c2Radius = c2.GetRadius();
	float radiusSum = c1Radius + c2Radius;

	float distance = std::sqrt(distanceSq);
	// 重なっている距離
	manifold.depth = radiusSum - distance;

	// 衝突法線
	manifold.normal = Vector2{ distanceX / distance, distanceY / distance };

	// 接触点
	manifold.contactPoint = c1.GetCenter() + (manifold.normal * c1Radius);

	// 位置の補正
	Vector2 push = manifold.normal * manifold.depth * 0.5f;
	c1.SetForceAccumulator(c1.GetForceAccumulator() + push);
	c2.SetForceAccumulator(c2.GetForceAccumulator() + push * -1.0f);

	c1.SetColor(0xFF0000FF);
	c2.SetColor(0xFF0000FF);
}
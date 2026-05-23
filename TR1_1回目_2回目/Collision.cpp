#include "Collision.h"
#include <cmath>
#include <algorithm>
bool IsCollision(Circle& c1, Circle& c2) {
	Vector2 direction = c2.GetCenter() + c1.GetCenter() * -1.0f;
	float distance = Distance(c1.GetCenter(), c2.GetCenter());

	float c1Radius = c1.GetRadius();
	float c2Radius = c2.GetRadius();
	float radiusSum = c1Radius + c2Radius;

	// 衝突判定
	if (distance < radiusSum) {
		return true;
	}
	return false;
}

void Collide(Circle& c1, Circle& c2, Manifold& manifold) {
	Vector2 direction = c2.GetCenter() + c1.GetCenter() * -1.0f;
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
	manifold.normal = Normalize(direction);

	// 接触点
	manifold.contactPoint = c1.GetCenter() + (Normalize(direction) * c1Radius);
}

void ResolveCollision(Circle& c1, Circle& c2, const Manifold& manifold) {
	float relativeVelocityAlongNormal = Dot(c2.GetVelocity() - c1.GetVelocity(), manifold.normal);
	if (relativeVelocityAlongNormal > 0.0f)return;
	if (c1.GetInvMass() == 0.0f && c2.GetInvMass() == 0.0f)return;
	float e = std::min(c1.GetRestitution(),c2.GetRestitution());
	float invMassSum = c1.GetInvMass() + c2.GetInvMass();
	float j = (-(1.0f + e) * relativeVelocityAlongNormal) / invMassSum;
	Vector2 impulseVector = manifold.normal * j;
	c1.SetVelocity(c1.GetVelocity() + impulseVector * -c1.GetInvMass());
	c2.SetVelocity(c2.GetVelocity() + impulseVector * c2.GetInvMass());
}

void PositionalCorrection(Circle& c1, Circle& c2, const Manifold& manifold) {
	float correction = 0.7f;
	float correctionAmount = manifold.depth / (c1.GetInvMass() + c2.GetInvMass()) * correction;
	Vector2 correctionVector = manifold.normal * correctionAmount;
	if (c1.GetInvMass() > 0.0f) {
		c1.Translate(correctionVector * -c1.GetInvMass());
	}

	if (c2.GetInvMass() > 0) {
		c2.Translate(correctionVector * c2.GetInvMass());
	}
}
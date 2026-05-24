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
	Vector2 relativeVelocity = c2.GetVelocity() - c1.GetVelocity();
	float velAlongNormal = Dot(relativeVelocity, manifold.normal);

	if (velAlongNormal > 0) return;

	// WA法 
	float waFactor = 1.4f;
	float invMass1 = c1.GetInvMass();
	float invMass2 = c2.GetInvMass();

	// manifold.normal.y の向きを確認 (Y軸正が下向きと仮定)
	// normalは c1 から c2 へのベクトルから作られているので：
	// normal.y > 0 なら c2 が下
	// normal.y < 0 なら c1 が下
	if (manifold.normal.y > 0.1f) {
		invMass2 /= waFactor; // 下にあるc2を重くする
	} else if (manifold.normal.y < -0.1f) {
		invMass1 /= waFactor; // 下にあるc1を重くする
	}
	// ----------------

	float e = std::min(c1.GetRestitution(), c2.GetRestitution());

	// 調整後の invMass を使って計算
	float invMassSum = invMass1 + invMass2;
	if (invMassSum <= 0.0f) return;

	float j = (-(1.0f + e) * velAlongNormal) / invMassSum;
	Vector2 impulseVector = manifold.normal * j;

	// 速度への適用（ここでも調整後の invMass を使うことで下側が動きにくくなる）
	c1.SetVelocity(c1.GetVelocity() - impulseVector * invMass1);
	c2.SetVelocity(c2.GetVelocity() + impulseVector * invMass2);
}

void PositionalCorrection(Circle& c1, Circle& c2, const Manifold& manifold) {
	const float slop = 0.05f; // 許容するめり込み量
	const float percent = 0.7f; // 補正の強さ

	// --- WA法 導入 ---
	float waFactor = 1.4f;
	float invMass1 = c1.GetInvMass();
	float invMass2 = c2.GetInvMass();

	if (manifold.normal.y > 0.1f) {
		invMass2 /= waFactor; // c2が下なので重く
	} else if (manifold.normal.y < -0.1f) {
		invMass1 /= waFactor; // c1が下なので重く
	}
	// ----------------

	float invMassSum = invMass1 + invMass2;
	if (invMassSum <= 0.0f) return;

	float correctionAmount = (std::max(manifold.depth - slop, 0.0f) / invMassSum) * percent;
	Vector2 correctionVector = manifold.normal * correctionAmount;

	// 座標を直接ずらす
	c1.Translate(correctionVector * -invMass1);
	c2.Translate(correctionVector * invMass2);
}
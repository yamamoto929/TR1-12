#include "Circle.h"
#include <Novice.h>
#include "Integrate.h"
#include <cmath>
Circle::Circle(float r) {
	radius_ = r;
}

void Circle::Update() {
	SetGrounded(false);
	
	Vector2 gravity = { 0.0f, 0.4f };
	forceAccumulator_ = forceAccumulator_ + gravity * mass_;

	if (center_.y > 600.0f) {
		center_.y = 600.0f;

		//地面衝突時の速度減衰
		if (std::abs(velocity_.y) < 1.0f) { 
			velocity_.y = 0;              
		} else {
			velocity_.y *= -0.5f;         
		}
		// 地面との摩擦
		velocity_.x *= 0.8f;
	}

	if (GetCenter().y >= 600.0f - 1.0f) {
		SetGrounded(true);
	}
}
void Circle::Draw() const {
	Novice::DrawEllipse(
		int(center_.x), int(center_.y),
		int(radius_),
		int(radius_),
		angle_,
		color_,
		kFillModeSolid
	);
}

void Circle::Rotate(float angle) {
	angle_ += angle;
}
void Circle::Translate(const Vector2& offset) {
	center_.x += offset.x;
	center_.y += offset.y;
}
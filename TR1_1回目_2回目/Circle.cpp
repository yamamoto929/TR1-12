#include "Circle.h"
#include <Novice.h>
#include "Integrate.h"
Circle::Circle(float r) {
	radius_ = r;
}

void Circle::Update() {
	Vector2 gravity = { 0.0f,0.2f };
	forceAccumulator_ = forceAccumulator_ + gravity * mass_;
	if (center_.y > 600.0f) {
		center_.y = 600.0f;
		velocity_ = velocity_ * -1.0f;
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
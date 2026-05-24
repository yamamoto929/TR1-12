#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
	float radius_;
	bool isGrounded_ = false;

public:
	Circle(float r);

	void Rotate(float angle) override;
	void Translate(const Vector2& offset) override;

	void SetRadius(float r) { radius_ = r; }
	float GetRadius() const { return radius_; }

	void SetGrounded(bool grounded) { isGrounded_ = grounded; }
	bool IsGrounded()const { return isGrounded_; }

	void Update() override;

	void Draw() const override;
};
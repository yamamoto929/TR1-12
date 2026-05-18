#pragma once
#include "Shape.h"

class Circle : public Shape {
private:
	float radius_;

public:
	Circle(float r);

	void Rotate(float angle) override;
	void Translate(const Vector2& offset) override;

	void SetRadius(float r) { radius_ = r; }
	float GetRadius() const { return radius_; }

	void Update() override;

	void Draw() const override;
};
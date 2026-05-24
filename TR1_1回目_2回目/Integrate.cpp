#include "Integrate.h"
#include "Vector2.h"
#include "Novice.h"
#include "Circle.h"
void Integrate(Shape& shape) {
	Circle* circle = dynamic_cast<Circle*>(&shape);

	// 下に支えがあるかチェック
	bool isGrounded = false;
	if (circle) {
		isGrounded = circle->IsGrounded(); 
	}

	Vector2 acceleration = shape.GetForceAccumulator() * shape.GetInvMass();
	Vector2 velocity = shape.GetVelocity() + acceleration;
	// 速度の2乗が一定値以下なら停止
	float speedSq = velocity.x * velocity.x + velocity.y * velocity.y;

	if (isGrounded) {
		if (speedSq < 0.2f) { 
			velocity = { 0.0f, 0.0f };
		} else {
			velocity.x *= 0.9f; 
		}
	}
	shape.SetVelocity(velocity);
	shape.Translate(shape.GetVelocity());

	shape.SetForceAccumulator({ 0.0f,0.0f });
	shape.SetVelocity((shape.GetVelocity() * 0.98f));
}
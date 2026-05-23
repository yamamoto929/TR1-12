#include "Integrate.h"
#include "Vector2.h"
#include "Novice.h"
void Integrate(Shape& shape) {
	Vector2 acceleration = shape.GetForceAccumulator() * shape.GetInvMass();

	Vector2 velocity = shape.GetVelocity() + acceleration;
	shape.SetVelocity(velocity);
	shape.Translate(shape.GetVelocity());

	shape.SetForceAccumulator({ 0.0f,0.0f });
	shape.SetVelocity((shape.GetVelocity() * 0.98f));
}
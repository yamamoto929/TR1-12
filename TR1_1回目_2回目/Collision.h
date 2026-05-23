#pragma once
#include "Circle.h"
#include "Manifold.h"
bool IsCollision(Circle& c1,  Circle& c2);
void Collide(Circle& c1, Circle& c2, Manifold& manifold);
void ResolveCollision(Circle& c1, Circle& c2,const Manifold& manifold);
void PositionalCorrection(Circle& c1, Circle& c2, const Manifold& manifold);
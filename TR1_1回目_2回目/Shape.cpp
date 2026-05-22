#include "Shape.h"
Shape::Shape() {
    center_.x = 0.0f;
    center_.y = 0.0f;
    angle_ = 0.0f;
    color_ = 0x000000FF;
    invMass_ = 0.0f;
    mass_=0.0f;
    velocity_ = {};
    forceAccumulator_ = {};
}
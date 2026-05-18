#include "Circle.h"
#include <Novice.h>
Circle::Circle(float r) {
    radius_ = r;
}

void Circle::Update() {

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
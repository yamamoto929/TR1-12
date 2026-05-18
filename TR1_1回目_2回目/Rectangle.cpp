#include "Rectangle.h"
#include <Novice.h>
#include <cmath>
Rect::Rect(float w, float h) {
    SetSize(w, h);
    graphHandle_ = Novice::LoadTexture("white1x1.png");
}
void Rect::SetSize(float w, float h) {
    width_ = w;
    height_ = h;
    SetVertices();
}
void Rect::SetVertices() {
    float halfWidth = width_ / 2.0f;
    float halfHeight = height_ / 2.0f;

    Vector2 localVertices[4];
    localVertices[LEFTTOP] = Vector2{ -halfWidth, -halfHeight };
    localVertices[RIGHTTOP] = Vector2{ halfWidth, -halfHeight };
    localVertices[LEFTBOTTOM] = Vector2{ -halfWidth,  halfHeight };
    localVertices[RIGHTBOTTOM] = Vector2{ halfWidth,  halfHeight };

    float cos = std::cos(angle_);
    float sin = std::sin(angle_);

    for (int i = 0; i < 4; ++i) {
        vertices_[i].x = (localVertices[i].x * cos - localVertices[i].y * sin) + center_.x;
        vertices_[i].y = (localVertices[i].x * sin + localVertices[i].y * cos) + center_.y;
    }
}

void Rect::Update()  {

}

void Rect::Draw() const {
    Novice::DrawQuad(
        int(vertices_[Corner::LEFTTOP].x), int(vertices_[Corner::LEFTTOP].y),
        int(vertices_[Corner::RIGHTTOP].x), int(vertices_[Corner::RIGHTTOP].y),
        int(vertices_[Corner::LEFTBOTTOM].x), int(vertices_[Corner::LEFTBOTTOM].y),
        int(vertices_[Corner::RIGHTBOTTOM].x), int(vertices_[Corner::RIGHTBOTTOM].y),
        int(vertices_[Corner::LEFTTOP].x), int(vertices_[Corner::LEFTTOP].y),
        int(width_),
        int(height_),
        graphHandle_,
        color_
    );
}

void Rect::Rotate(float angle) {
    angle_ += angle;
    SetVertices();
}
void Rect::Translate(const Vector2& offset) {
    center_.x += offset.x;
    center_.y += offset.y;
    SetVertices();
}
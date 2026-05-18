#pragma once
#include "Shape.h"

class Rect : public Shape {
public:
    enum Corner {
        LEFTTOP,    // 0 左上
        RIGHTTOP,   // 1 右上
        LEFTBOTTOM, // 2 左下
        RIGHTBOTTOM // 3 右下
    };

private:
    Vector2 vertices_[4];
    float width_;
    float height_;
    unsigned int graphHandle_;

public:
    Rect(float w = 0.0f, float h = 0.0f);
    void Rotate(float angle) override;
    void Translate(const Vector2& offset)override;
    void SetSize(float w, float h);
    void SetVertices();

    // 基底クラスの純粋仮想関数をオーバーライド
    void Update() override;

    void Draw() const override;
};
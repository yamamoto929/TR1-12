#pragma once
#include "Vector2.h"

class Shape {
protected:
    Vector2 center_;
    float angle_;
    unsigned int color_;

public:
    Shape();

    // デストラクタ
    virtual ~Shape() = default;

    // 派生クラスで必ず実装させる
    virtual void Update() = 0;
    virtual void Draw() const = 0;
    virtual void Rotate(float angle) = 0;
    virtual void Translate(const Vector2& offset) = 0;

    // セッターゲッター
    void SetCenter(const Vector2& c) { center_ = c; }
    void SetAngle(float a) { angle_ = a; }
    void SetColor(unsigned int c) { color_ = c; }
    Vector2 GetCenter() const { return center_; }
};
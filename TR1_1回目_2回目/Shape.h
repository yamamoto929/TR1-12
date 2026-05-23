#pragma once
#include "Vector2.h"

class Shape {
protected:
	Vector2 center_;
	float mass_;
	float invMass_; // 質量の逆数
	Vector2 velocity_ = {};
	float angle_;
	Vector2 forceAccumulator_ = {}; // 力の蓄積
	unsigned int color_;
	float friction_;
	float restitution_;

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
	void SetCenter(Vector2 c) { center_ = c; }
	void SetAngle(float a) { angle_ = a; }
	void SetColor(unsigned int c) { color_ = c; }
	void SetMass(float m) { mass_ = m;  invMass_ = mass_ == 0.0f ? 0.0f : 1.0f / mass_; }
	void SetVelocity(Vector2 v) { velocity_ = v; }
	void SetForceAccumulator(Vector2 f) { forceAccumulator_ = f; }
	Vector2 GetCenter() const { return center_; }
	Vector2 GetVelocity() const { return velocity_; }
	Vector2 GetForceAccumulator() const { return forceAccumulator_; }
	float GetMass()const { return mass_; }
	float GetInvMass()const { return invMass_; }
	float GetRestitution()const { return restitution_; }
};
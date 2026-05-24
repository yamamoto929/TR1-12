#include <Novice.h>
#include <vector>
#include "Circle.h"
#include "Rectangle.h"
#include "Collision.h"
#include "Integrate.h"


const char kWindowTitle[] = "TR1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::vector<Circle*> circles;
	std::vector<Manifold> manifolds;

	Circle* circle1 = new Circle(50.0f);
	circle1->SetCenter({ 600.0f, 160.0f });
	circle1->SetMass(1.0f);

	Circle* circle2 = new Circle(50.0f);
	circle2->SetCenter({ 550.0f, 300.0f });
	circle2->SetMass(1.0f);


	circles.push_back(circle1);
	circles.push_back(circle2);
	int mousePosX;
	int mousePosY;
	// bool drawManifold = false;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		manifolds.clear();
		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///	
		if (Novice::IsTriggerMouse(0)) {
			Novice::GetMousePosition(&mousePosX, &mousePosY);
			Circle* circle = new Circle(50.0f);
			Vector2 mouseVector2{ float(mousePosX),float(mousePosY) };
			circle->SetCenter(mouseVector2);
			circle->SetMass(1.0f);
			circles.push_back(circle);
		}

		for (Circle* circle : circles) {
			if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
				circle->SetCenter(circle->GetCenter() + Vector2{ 0.0f,-300.0f });
			}
			circle->Update();
		}

		for (size_t i = 0; i < circles.size(); i++) {
			for (size_t j = i + 1; j < circles.size(); j++) {
				if (i == j) { continue; }
				Circle* c1 = circles[i];
				Circle* c2 = circles[j];

				Manifold manifold{};
				if (IsCollision(*c1, *c2)) {
					Collide(*c1, *c2, manifold);

					// 位置補正と速度解決を行う
					PositionalCorrection(*c1, *c2, manifold);
					ResolveCollision(*c1, *c2, manifold);


					manifolds.push_back(manifold);


					// 法線のY成分を見て、どっちが上か下か判定する
					if (std::abs(manifold.normal.y) > 0.5f) {
						if (manifold.normal.y > 0.0f) {
							if (c2->IsGrounded()) { c1->SetGrounded(true); }
						} else {
							if (c1->IsGrounded()) { c2->SetGrounded(true); }
						}
					}
				}
			}
		}


		for (Circle* circle : circles) {
			Integrate(*circle);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (Circle* circle : circles) {
			circle->Draw();
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	for (Shape* shape : circles) {
		delete shape;
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

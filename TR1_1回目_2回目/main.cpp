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
	circle2->SetCenter({ 500.0f, 300.0f });
	circle2->SetMass(1.0f);

	Circle* circle3 = new Circle(50.0f);
	circle3->SetCenter({ 400.0f, 400.0f });
	circle3->SetMass(1.0f);

	circles.push_back(circle1);
	circles.push_back(circle2);
	circles.push_back(circle3);


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
		circle1->Rotate(0.1f);
		circle2->Rotate(0.1f);

		circle1->Translate(Vector2{ -0.1f,0.1f });
		//circle2->Translate(Vector2{ 0.2f,0.2f });

		for (size_t i = 0;i < circles.size(); i++) {
			for (size_t j = i ;j < circles.size(); j++) {
				if (i == j) { continue; }
				Circle* c1 = circles[i];
				Circle* c2 = circles[j];

				Manifold manifold{};
				if (IsCollision(*c1, *c2)) {
					Collide(*c1, *c2, manifold);
				} else {
					c1->SetColor(0x000000FF);
					c2->SetColor(0x000000FF);
				}
				manifolds.push_back(manifold);
			}
		}

		int a = 0;
		for (Circle* circle : circles) {
			a++;
			Novice::ConsolePrintf("c%d",a);
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

		for (size_t i = 0;i < circles.size(); i++) {
			Circle* c1 = circles[i];
			Novice::ScreenPrintf(0, 0 + int(i) * 20, "circle%d->center_ : %f , %f\n", int(i), c1->GetCenter().x, c1->GetCenter().y);
			Novice::ScreenPrintf(int(c1->GetCenter().x), int(c1->GetCenter().y), "c%d", int(i));
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

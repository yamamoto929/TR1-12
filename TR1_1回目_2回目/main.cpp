#include <Novice.h>
#include <vector>
#include "Circle.h"
#include "Rectangle.h"

const char kWindowTitle[] = "TR1";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	std::vector<Shape*> shapes;

	Circle* circle = new Circle(100.0f);
	circle->SetCenter({ 200.0f, 200.0f });

	Rect* rect = new Rect(100.0f, 60.0f);
	rect->SetCenter({ 500.0f, 500.0f });
	rect->SetVertices();

	shapes.push_back(circle);
	shapes.push_back(rect);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		rect->Rotate(0.01f);
		circle->Rotate(0.01f);
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		for (Shape* shape : shapes) {
			shape->Draw();
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

	for (Shape* shape : shapes) {
		delete shape;
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

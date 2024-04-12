#include <Novice.h>
#include "MyFunc.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_00_01";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vec3 v1 = { 1.0f,3.0f,-5.0f };
	Vec3 v2 = { 4.0f,-1.0f,2.0f };
	float k = 4.0f;

	const int kRowHeight = 20;

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VecScreenPrintf(0, 0, Add(v1, v2), ":Add");
		VecScreenPrintf(0, kRowHeight * 1, Subtract(v1, v2), ":Subtract");
		VecScreenPrintf(0, kRowHeight * 2, Multiply(v1, k), ":Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%f : Dot", Dot(v1, v2));
		Novice::ScreenPrintf(0, kRowHeight * 4, "%f : Length", Length(v1));
		VecScreenPrintf(0, kRowHeight * 5, Normalize(v2), ":Normalize");

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

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

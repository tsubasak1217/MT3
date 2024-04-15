#include <Novice.h>
#include "MyFunc.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3__";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Matrix4x4 orthoMatrix = OrthoMatrix(-160.0f, 200.0f, 160.0f, 300.0f, 0.0f,1000.0f);
	Matrix4x4 perspectiveMatrix = PerspectiveMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix4x4 viewportMatrix = ViewportMatrix({ 600.0f,300.0f }, { 100.0f,200.0f }, 0.0f, 1.0f);
	const int kRowHeight = 120;


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

		MatrixScreenPrintf(0, 0, orthoMatrix, "orthoMatrix");
		MatrixScreenPrintf(0, kRowHeight, perspectiveMatrix, "perspectiveMatrix");
		MatrixScreenPrintf(0, kRowHeight * 2, viewportMatrix, "viewportMatrix");

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

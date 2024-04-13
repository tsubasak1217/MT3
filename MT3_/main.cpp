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

	Matrix4x4 m1(
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f
	);

	Matrix4x4 m2(
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
	);

	int kRowHeight = 120;
	int kColWidth = 280;

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

		MatrixScreenPrintf(0, 0, Add(m1,m2),"Add");
		MatrixScreenPrintf(0, kRowHeight * 1, Subtract(m1, m2), "Subtract");
		MatrixScreenPrintf(0, kRowHeight * 2, Multiply(m1, m2), "Multiply");
		MatrixScreenPrintf(0, kRowHeight * 3, InverseMatrix(m1), "InverseM1");
		MatrixScreenPrintf(0, kRowHeight * 4, InverseMatrix(m2), "InverseM2");

		MatrixScreenPrintf(kColWidth * 1, 0, Transpose(m1), "TransposeM1");
		MatrixScreenPrintf(kColWidth * 1, kRowHeight * 1, Transpose(m2), "TransposeM2");
		MatrixScreenPrintf(kColWidth * 1, kRowHeight * 2, IdentityMat4(), "Identtity");

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

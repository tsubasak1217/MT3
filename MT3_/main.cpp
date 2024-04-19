#include <Novice.h>
#include "MyFunc.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_01_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	struct Triangle {

		Vec3 rotate_ = { 0.0f,0.0f,0.0f };
		Vec3 translate_ = { 0.0f,0.0f,10.0f };
		Matrix4x4 worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, rotate_, translate_);
		float moveSpeed_ = 2.0f;

		Vec3 localVertexes_[3] = {
			{ 0.0f,  0.5f, 0.0f},
			{ 0.5f, -0.5f, 0.0f},
			{-0.5f, -0.5f, 0.0f}
		};
	};

	struct Camera {
		Vec3 translate_ = { 0.0f,0.0f,0.0f };
		Matrix4x4 worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate_);
	};


	Vec3 v1(1.2f, -3.9f, 2.5f);
	Vec3 v2(2.8f, 0.4f, -1.3f);
	Vec3 cross = Cross(v1, v2);

	Triangle triangle;
	Camera camera;

	Matrix4x4 viewMatrix = InverseMatrix(camera.worldMatrix_);
	Matrix4x4 perspectiveMatrix = PerspectiveMatrix(0.63f, 1.33f, 0.1f, 1000.0f);
	Matrix4x4 viewportMatrix = ViewportMatrix({ 1280,720 }, { 0.0f,0.0f }, 0.0f, 1000.0f);
	Matrix4x4 wvpVpMatrix;



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

		triangle.rotate_ += 0.03f;

		if (keys[DIK_A]) { triangle.translate_.x -= triangle.moveSpeed_; };
		if (keys[DIK_D]) { triangle.translate_.x += triangle.moveSpeed_; };
		if (keys[DIK_W]) { triangle.translate_.z += triangle.moveSpeed_; };
		if (keys[DIK_S]) { triangle.translate_.z -= triangle.moveSpeed_; };

		triangle.worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, triangle.rotate_, triangle.translate_);
		camera.worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, camera.translate_);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VecScreenPrintf(5, 5, cross, ":Cross");

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

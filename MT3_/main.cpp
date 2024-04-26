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
		float moveSpeed_ = 0.20f;
		float radius = 0.5f;

		Vec3 localVertexes_[3] = {
			{ 0.0f,  radius, 0.0f},
			{ radius, -radius, 0.0f},
			{-radius, -radius, 0.0f}
		};
	};

	struct Camera {
		Vec3 translate_ = { 0.0f,0.0f,0.0f };
		Matrix4x4 worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, translate_);
	};

	Vec3 v1(1.2f, -3.9f, 2.5f);
	Vec3 v2(2.8f, 0.4f, -1.3f);
	Vec3 debugCross = Cross(v1, v2, kScreen);

	Triangle triangle;
	Camera camera;

	Matrix4x4 viewMatrix = InverseMatrix(camera.worldMatrix_);
	float zNear = 0.1f;
	float zFar = 100.0f;
	Matrix4x4 perspectiveMatrix = PerspectiveMatrix(0.45f, AspectRatio(1280.0f, 720.0f), zNear, zFar);
	Matrix4x4 viewportMatrix = ViewportMatrix({ 1280,720 }, { 0.0f,0.0f }, 0.0f, zFar);
	Matrix4x4 wvpVpMatrix;

	Vec3 cross;
	float dot;

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

		triangle.rotate_.y += 0.03f;

		if (keys[DIK_A]) { triangle.translate_.x -= triangle.moveSpeed_; };
		if (keys[DIK_D]) { triangle.translate_.x += triangle.moveSpeed_; };
		if (keys[DIK_W]) { triangle.translate_.z += triangle.moveSpeed_; };
		if (keys[DIK_S]) { triangle.translate_.z -= triangle.moveSpeed_; };

		triangle.worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, triangle.rotate_, triangle.translate_);
		camera.worldMatrix_ = AffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, camera.translate_);
		wvpVpMatrix =
			Multiply(
				Multiply(triangle.worldMatrix_, viewMatrix),
				Multiply(perspectiveMatrix, viewportMatrix)
			);

		Vec3 screenVertexes[3];
		screenVertexes[0] = Multiply(triangle.localVertexes_[0], wvpVpMatrix);
		screenVertexes[1] = Multiply(triangle.localVertexes_[1], wvpVpMatrix);
		screenVertexes[2] = Multiply(triangle.localVertexes_[2], wvpVpMatrix);

		cross = Cross(
			screenVertexes[1] - screenVertexes[0],
			screenVertexes[2] - screenVertexes[1],
			kScreen
		);
		dot = Dot({ 0.0f,0.0f,1.0f }, cross);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		if (triangle.translate_.z >= zNear + triangle.radius) {
			if (dot < 0.0f) {
				Novice::DrawTriangle(
					int(screenVertexes[0].x), int(screenVertexes[0].y),
					int(screenVertexes[1].x), int(screenVertexes[1].y),
					int(screenVertexes[2].x), int(screenVertexes[2].y),
					0xff0000ff,
					kFillModeSolid
				);
			}
		}

		VecScreenPrintf(5, 5, debugCross, ":Cross");
		VecScreenPrintf(5, 25, triangle.translate_, ":TrianglePos");
		Novice::ScreenPrintf(5, 45, "%f:dot", dot);

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

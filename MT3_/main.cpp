#include <Novice.h>
#include "MyFunc.h"
#include <ImGui.h>

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_01_00";

struct Camera {
	Vec3 scale_ = { 1.0f,1.0f,1.0f };
	Vec3 rotate_ = { 0.26f,0.0f,0.0f };
	Vec3 translate_ = { 0.0f,1.9f,-6.49f };

	Vec3 direction_ = { 0.0f,0.0f,1.0f };
	
	Vec3 lerpRotate_ = rotate_;
	Vec3 lerpTranslate_ = translate_;

	Matrix4x4 worldMatrix_ = AffineMatrix(scale_, rotate_, translate_);
	float rotateRate_ = 1.0f / 120.0f * 3.14f;
};

Camera camera;

Matrix4x4 viewMatrix = InverseMatrix(camera.worldMatrix_);
float zNear = 0.1f;
float zFar = 100.0f;
Matrix4x4 perspectiveMatrix = PerspectiveMatrix(0.45f, AspectRatio(1280.0f, 720.0f), zNear, zFar);
Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, perspectiveMatrix);
Matrix4x4 viewportMatrix = ViewportMatrix({ 1280,720 }, { 0.0f,0.0f }, 0.0f, zFar);
Matrix4x4 wvpVpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);

void UpdateMatrix() {
	camera.worldMatrix_ = AffineMatrix(camera.scale_, camera.rotate_, camera.translate_);
	viewMatrix = InverseMatrix(camera.worldMatrix_);
	perspectiveMatrix = PerspectiveMatrix(0.45f, AspectRatio(1280.0f, 720.0f), zNear, zFar);
	viewProjectionMatrix = Multiply(viewMatrix, perspectiveMatrix);
	viewportMatrix = ViewportMatrix({ 1280,720 }, { 0.0f,0.0f }, 0.0f, zFar);
	wvpVpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		ImGui::Begin("camera");
		ImGui::DragFloat3("scale", &camera.scale_.x, 0.02f);
		ImGui::DragFloat3("rotate", &camera.lerpRotate_.x, camera.rotateRate_);
		ImGui::DragFloat3("translate", &camera.lerpTranslate_.x, 0.2f);
		ImGui::End();

		camera.direction_ = Multiply({ 0.0f,0.0f,1.0f }, RotateMatrix(camera.rotate_));
		camera.lerpTranslate_ += camera.direction_ * (float(Novice::GetWheel() > 0) * 0.5f);
		camera.lerpTranslate_ -= camera.direction_ * (float(Novice::GetWheel() < 0) * 0.5f);

		// 移動をする
		camera.translate_ += (camera.lerpTranslate_ - camera.translate_) * 0.0625f;
		camera.rotate_ += (camera.lerpRotate_ - camera.rotate_) * 0.0625f;

		UpdateMatrix();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

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

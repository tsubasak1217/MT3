#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_01_02";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());
	Sphere sphere(
		{ 1.0f,1.0f,1.0f },// Size
		{ 1.0f,1.0f,1.0f },// Scale
		{ 0.0f,0.0f,0.0f },// Rotate
		{ 0.0f,0.0f,0.0f },// Translate
		renderMat.GetViewProjectionMat(),
		renderMat.GetViewportMat()
	);

	// ウィンドウの×ボタンが押されるまでループ
	while(Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Camera");
		ImGui::DragFloat3("rotate", &camera->lerpRotate_.x, camera->rotateRate_);
		ImGui::DragFloat3("translate", &camera->lerpTranslate_.x, 0.2f);
		ImGui::End();

		ImGui::Begin("Sphere");
		ImGui::DragFloat3("size", &sphere.size_.x, 0.02f);
		ImGui::DragFloat3("scale", &sphere.scale_.x,0.02f);
		ImGui::DragFloat3("rotate", &sphere.rotate_.x, 3.14f * 0.025f);
		ImGui::DragFloat3("translate", &sphere.translate_.x, 0.05f);
		ImGui::End();

		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
			sphere.Init(
				{ 1.0f,1.0f,1.0f },// Size
				{ 1.0f,1.0f,1.0f },// Scale
				{ 0.0f,0.0f,0.0f },// Rotate
				{ 0.0f,0.0f,0.0f },// Translate
				renderMat.GetViewProjectionMat(),
				renderMat.GetViewportMat()
			);
		}

		// レンダリング用の行列とか更新
		camera->Update();
		renderMat.Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());
		sphere.Draw(16, 0xff0000ff);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if(preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

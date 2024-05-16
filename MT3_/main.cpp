#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_02_01";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	Sphere sphere[2];

	sphere[0].Init(
		{ 0.5f,0.5f,0.5f },// Size
		{ 1.0f,1.0f,1.0f },// Scale
		{ 0.0f,0.0f,0.0f },// Rotate
		{ 1.0f,0.0f,1.0f },// Translate
		renderMat.GetViewProjectionMat(),
		renderMat.GetViewportMat()
	);

	sphere[1].Init(
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
		ImGui::Text("[ CLICK WHEEL & MOVE MOUSE ] -> moveCamera");
		ImGui::End();

		ImGui::Begin("Sphere1");
		ImGui::DragFloat("scale", &sphere[0].scale_.x, 0.02f,0.0f);
		sphere[0].scale_ = { sphere[0].scale_.x ,sphere[0].scale_.x ,sphere[0].scale_.x };
		sphere[0].radius_ = sphere[0].size_.x * sphere[0].scale_.x * 0.5f;
		ImGui::DragFloat3("rotate", &sphere[0] .rotate_.x, 3.14f * 0.025f);
		ImGui::DragFloat3("translate", &sphere[0].translate_.x, 0.05f);
		ImGui::End();

		ImGui::Begin("Sphere2");
		ImGui::DragFloat("scale", &sphere[1].scale_.x, 0.02f, 0.0f);
		sphere[1].scale_ = { sphere[1].scale_.x ,sphere[1].scale_.x ,sphere[1].scale_.x };
		sphere[1].radius_ = sphere[1].size_.x * sphere[1].scale_.x * 0.5f;
		ImGui::DragFloat3("rotate", &sphere[1].rotate_.x, 3.14f * 0.025f);
		ImGui::DragFloat3("translate", &sphere[1].translate_.x, 0.05f);
		ImGui::End();

		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
			sphere[0].Init(
				{ 0.5f,0.5f,0.5f },// Size
				{ 1.0f,1.0f,1.0f },// Scale
				{ 0.0f,0.0f,0.0f },// Rotate
				{ 1.0f,0.0f,1.0f },// Translate
				renderMat.GetViewProjectionMat(),
				renderMat.GetViewportMat()
			);

			sphere[1].Init(
				{ 1.0f,1.0f,1.0f },// Size
				{ 1.0f,1.0f,1.0f },// Scale
				{ 0.0f,0.0f,0.0f },// Rotate
				{ 0.0f,0.0f,0.0f },// Translate
				renderMat.GetViewProjectionMat(),
				renderMat.GetViewportMat()
			);

		}

		if(Collision_Sphere_Sphere(sphere[0], sphere[1])){
			sphere[1].color_ = 0xff0000ff;
		} else{
			sphere[1].color_ = 0xffffffff;
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

		// グリッド
		DrawGrid(renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());

		// 球
		for(int i = 0; i < 2; i++){
			sphere[i].Draw(16);
		}

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

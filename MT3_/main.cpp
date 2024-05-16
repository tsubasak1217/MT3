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

	int pushCount = 0;

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

		ImGui::Begin("Sphere1");
		ImGui::DragFloat3("size", &sphere[0].size_.x, 0.02f,0.0f);
		ImGui::DragFloat3("rotate", &sphere[0] .rotate_.x, 3.14f * 0.025f);
		ImGui::DragFloat3("translate", &sphere[0].translate_.x, 0.05f);
		ImGui::End();

		ImGui::Begin("Sphere2");
		ImGui::DragFloat3("size", &sphere[1].size_.x, 0.02f,0.0f);
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

			pushCount = 0;
		}

		if(Collision_Sphere_Sphere(sphere[0], sphere[1])){
			sphere[0].color_ = 0xff0000ff;
		} else{
			sphere[0].color_ = 0xffffffff;
		}

		if(keys[DIK_SPACE] && !preKeys[DIK_SPACE]){
			pushCount++;

			if(pushCount == 1){
				Collision_Sphere_Sphere(&sphere[0], &sphere[1]);
			} else if(pushCount == 2){
				Collision_Sphere_Sphere2(&sphere[0], &sphere[1]);
			} else if(pushCount == 3){
				Collision_Sphere_Sphere3(&sphere[0], &sphere[1]);
			} else if(pushCount == 4){
				Collision_Sphere_Sphere4(&sphere[0], &sphere[1]);
			} else{
				Collision_Sphere_Sphere5(&sphere[0], &sphere[1]);
				pushCount = 0;
			}
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

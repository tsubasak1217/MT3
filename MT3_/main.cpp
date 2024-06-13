#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_02_07";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	AABB aabb({ -2.0f, 0.0f, -2.0f }, { -1.0f,1.0f,-1.0f });

	EqualSphere sphere(
		0.5f, 1.0f, { 0.0f,0.0f,0.0f }, { 1.0f,0.5f,1.0f },
		renderMat.GetViewProjectionMat(), renderMat.GetViewportMat()
	);

	OBB obb(
		{ 0.0f, 0.0f, 0.0f },//center
		{ 0.1f, 0.2f, 1.3f },//rotate
		{ 0.5f, 0.5f, 0.5f }//size
	);

	int subdivision = 16;

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

		ImGui::Begin("OBB");
		ImGui::DragFloat3("center", &obb.center.x, 0.1f);
		ImGui::DragFloat3("rotate", &obb.rotate.x, 0.005f);
		ImGui::DragFloat3("size", &obb.size.x, 0.01f);
		ImGui::End();

		ImGui::Begin("Sphere");
		ImGui::DragFloat3("translate", &sphere.translate_.x, 0.05f);
		ImGui::DragFloat("size", &sphere.radius_, 0.05f);
		ImGui::End();



		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
		}

		// レンダリング用の行列とか更新
		camera->Update();
		renderMat.Update();

		if(Collision_OBB_Sphere(obb,sphere)){
			obb.color = 0xff0000ff;
		} else{
			obb.color = 0xffffffff;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());

		// AABB
		DrawOBB(obb, *renderMat.GetViewProjectionMat(), *renderMat.GetViewportMat(), obb.color);

		// sphere
		sphere.Draw(subdivision);

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

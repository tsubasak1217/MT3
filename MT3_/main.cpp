#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_02_03";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	Line line({ -1.0f,-0.5f,-0.5f }, { 1.0f,0.5f,0.5f },SEGMENT);
	Plane plane(
		{ 0.0f,1.0f,0.0f },
		{ 0.0f,0.0f,0.0f },
		2.0f
	);

	plane.SetVpVp(
		renderMat.GetViewProjectionMat(),
		renderMat.GetViewportMat()
	);

	line.Init({ -1.0f,-0.5f,-0.5f }, { 1.0f,0.5f,0.5f }, SEGMENT);


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

		ImGui::Begin("Line");
		ImGui::DragFloat3("origin", &line.origin_.x, 0.01f);
		ImGui::DragFloat3("end", &line.end_.x,0.01f);
		ImGui::InputInt("LineType", &line.type_);
		ImGui::Text("Type: SEGMENT = 0, RAY = 1, LINE = 2");
		ImGui::End();

		ImGui::Begin("Plane");
		ImGui::DragFloat3("translate", &plane.centerPos_.x, 0.01f);
		ImGui::DragFloat3("rotate", &plane.rotate_.x, 3.14f * 0.005f);
		ImGui::End();

		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
			line.Init({ -1.0f,-0.5f,-0.5f }, { 1.0f,0.5f,0.5f },SEGMENT);

		}

		// レンダリング用の行列とか更新
		camera->Update();
		renderMat.Update();
		plane.Update();

		if(Collision_Plane_Line(plane,line)){
			line.color_ = 0xff0000ff;
		} else{
			line.color_ = 0xffffffff;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());

		// 線
		DrawSegment(line, *renderMat.GetViewProjectionMat(), *renderMat.GetViewportMat(), line.color_);

		// 平面
		plane.Draw();

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

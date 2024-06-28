#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "RenderMatrixes.h"
#include <random>

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_03_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	std::vector<Vec3>controlPoints(1, { 0.0f,0.0f,0.0f });

	const int kMaxPoints = 7;
	for(int32_t i = 0; i < kMaxPoints; i++){

		int prev = Clamp(i - 1, 0, i);

		Vec3 vec = Normalize({
			(float)((std::rand() % 100) - 50),
			(float)((std::rand() % 100) - 50),
			(float)((std::rand() % 100) - 50)
		});

		controlPoints.push_back(
			controlPoints[prev] + vec
		);
	}

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
		//ImGui::Text("Center");
		//ImGui::DragFloat3("OBB_1##1", &obb[0].center.x, 0.1f);
		//ImGui::DragFloat3("OBB_2##1", &obb[1].center.x, 0.1f);
		//ImGui::Text("Rotate");
		//ImGui::DragFloat3("OBB_1##2", &obb[0].rotate.x, 0.005f);
		//ImGui::DragFloat3("OBB_2##2", &obb[1].rotate.x, 0.005f);
		//ImGui::Text("Translate");
		//ImGui::DragFloat3("OBB_1##3", &obb[0].size.x, 0.01f);
		//ImGui::DragFloat3("OBB_2##3", &obb[1].size.x, 0.01f);
		ImGui::End();


		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
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

		// スプライン曲線
		DrawSpline3D(controlPoints, 32, 0xffffffff,renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());


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

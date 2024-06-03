#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "Plane.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_02_04";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	AABB aabb[2] = { 
		AABB({ -2.0f, 0.0f, -2.0f }, { -1.0f,1.0f,-1.0f }),
		AABB({ 1.0f, 0.0f, 1.0f }, { 2.0f,1.0f,2.0f })
	};

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

		ImGui::Begin("AABB");
		ImGui::Text("AABB[0]");
		ImGui::DragFloat3("point1##0", &aabb[0].point[0].x,0.1f);
		ImGui::DragFloat3("point2##0", &aabb[0].point[1].x, 0.1f);
		ImGui::Text("AABB[1]");
		ImGui::DragFloat3("point1##1", &aabb[1].point[0].x, 0.1f);
		ImGui::DragFloat3("point2##1", &aabb[1].point[1].x, 0.1f);
		ImGui::End();

		for(int i = 0; i < 2; i++){
			aabb[i].UpdateMinMax();
		}


		// Rキーでリセット
		if(keys[DIK_R]) {
			camera->Init();
		}

		// レンダリング用の行列とか更新
		camera->Update();
		renderMat.Update();

		if(Collision_AABB_AABB(aabb[0],aabb[1])){
			aabb[0].color = 0xff0000ff;
		} else{
			aabb[0].color = 0xffffffff;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// グリッド
		DrawGrid(renderMat.GetViewProjectionMat(), renderMat.GetViewportMat());

		for(int i = 0; i < 2; i++){
			DrawAABB(aabb[i], *renderMat.GetViewProjectionMat(), *renderMat.GetViewportMat(),aabb[i].color);
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

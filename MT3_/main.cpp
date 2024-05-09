#include <Novice.h>
#include <ImGui.h>
#include "MyFunc.h"
#include "Camera.h"
#include "Sphere.h"
#include "RenderMatrixes.h"

const char kWindowTitle[] = "LE2A_12_クロカワツバサ_MT3_02_00";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = std::make_unique<Camera>(Camera());
	RenderMatrixes renderMat(camera.get());

	Segment seg({-2.0f,-1.0f,0.0f},{3.0f,2.0f,2.0f});
	Vec3 point(-1.5f, 0.6f, 0.6f);
	Sphere sphere[2];

	sphere[0].Init(
		{ 0.03f,0.03f,0.03f },// Size
		{ 1.0f,1.0f,1.0f },// Scale
		{ 0.0f,0.0f,0.0f },// Rotate
		point,// Translate
		renderMat.GetViewProjectionMat(),
		renderMat.GetViewportMat()
	);

	sphere[1].Init(
		{ 0.03f,0.03f,0.03f },// Size
		{ 1.0f,1.0f,1.0f },// Scale
		{ 0.0f,0.0f,0.0f },// Rotate
		ClosestPoint(point,seg.origin_,seg.end_),// Translate
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

		ImGui::Begin("Point");
		ImGui::DragFloat3("position", &point.x, 0.1f);
		ImGui::End();

		ImGui::Begin("Segment");
		ImGui::DragFloat3("origin", &seg.origin_.x, 0.1f);
		ImGui::DragFloat3("end", &seg.end_.x, 0.1f);
		ImGui::End();


		sphere[0].translate_ = point;
		sphere[1].translate_ = ClosestPoint(point, seg.origin_, seg.end_);

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
		
		// 線分
		DrawSegment(
			seg,
			*renderMat.GetViewProjectionMat(),
			*renderMat.GetViewportMat(),
			0xffffffff
		);

		// 球
		for(int i = 0; i < 2; i++){
			sphere[i].Draw(16, 0xff0000ff - (0xff000000 * i));
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

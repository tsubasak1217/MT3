#include "Camera.h"

Camera::Camera() {
	Init();
}

Camera::~Camera() {
	Fin();
}

void Camera::Init() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.26f,0.0f,0.0f };
	translate_ = { 0.0f,1.9f,-6.49f };

	direction_ = { 0.0f,0.0f,1.0f };

	lerpRotate_ = rotate_;
	lerpTranslate_ = translate_;

	worldMatrix_ = AffineMatrix(scale_, rotate_, translate_);
	rotateRate_ = 1.0f / 120.0f * 3.14f;
}

void Camera::Update() {
	//
	direction_ = Multiply({ 0.0f,0.0f,1.0f }, RotateMatrix(rotate_));
	lerpTranslate_ += direction_ * (float(Novice::GetWheel() > 0) * 0.5f);
	lerpTranslate_ -= direction_ * (float(Novice::GetWheel() < 0) * 0.5f);

	// 移動をする
	translate_ += (lerpTranslate_ - translate_) * 0.0625f;
	rotate_ += (lerpRotate_ - rotate_) * 0.0625f;

	// ワールド行列の更新
	worldMatrix_ = AffineMatrix(scale_, rotate_, translate_);
}

void Camera::Fin() {
}

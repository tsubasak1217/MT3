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
	rotateRate_ = (1.0f / 512.0f) * 3.14f;
}

void Camera::Update() {
	//
	Novice::GetMousePosition(&mousePos_.x, &mousePos_.y);
	direction_ = Multiply({ 0.0f,0.0f,1.0f }, RotateMatrix(rotate_));

	if(Novice::IsTriggerMouse(2)){
		Novice::GetMousePosition(&clickPos_.x, &clickPos_.y);
		tmpTranslate_ = translate_;
		tmpRotate_ = rotate_;
	}

	if(Novice::IsPressMouse(2)){
		float phi = rotateRate_ * (clickPos_.x - mousePos_.x);
		float theta = rotateRate_ * (clickPos_.y - mousePos_.y);

		float tmpTranslateX = tmpTranslate_.x * std::cos(theta) - tmpTranslate_.y * std::sin(theta);
		//translate_.y = tmpTranslate_.x * std::sin(theta) + tmpTranslate_.y * std::cos(theta);
		tmpTranslateX; phi; theta;
		translate_.x = tmpTranslate_.x * std::cos(phi) - tmpTranslate_.z * std::sin(phi);
		translate_.z = tmpTranslate_.x * std::sin(phi) + tmpTranslate_.z * std::cos(phi);

		rotate_.y = tmpRotate_.y - phi;
		//rotate_.x = tmpRotate_.x + theta;


		lerpRotate_ = rotate_;
		lerpTranslate_ = translate_;

	} else{
		lerpTranslate_ += direction_ * (float(Novice::GetWheel() > 0) * 0.5f);
		lerpTranslate_ -= direction_ * (float(Novice::GetWheel() < 0) * 0.5f);
	}

	// 移動をする
	translate_ += (lerpTranslate_ - translate_) * 0.0625f;
	rotate_ += (lerpRotate_ - rotate_) * 0.0625f;

	// ワールド行列の更新
	worldMatrix_ = AffineMatrix(scale_, rotate_, translate_);
}

void Camera::Fin() {
}

#pragma once
#include "VectorN.h"
#include "MatrixNxN.h"
#include "MyFunc.h"

class Camera {
public:
	Camera();
	~Camera();
	void Init();
	void Update();
	void Fin();

public:
	Vec3 scale_;
	Vec3 rotate_;
	Vec3 translate_;

	Vec3 direction_;

	Vec3 lerpRotate_;
	Vec3 lerpTranslate_;

	Vector2<int> clickPos_;
	Vector2<int> mousePos_;
	Vector2<int> preMousePos_;
	Vec3 tmpTranslate_;
	Vec3 tmpRotate_;

	Matrix4x4 worldMatrix_;
	float rotateRate_;
};
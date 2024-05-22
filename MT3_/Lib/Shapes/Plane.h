#pragma once
#include "VectorN.h"
#include "MatrixNxN.h"

struct Plane{
	Vec3 centerPos_;
	Vec3 rotate_;
	float size_;
	Vec3 normalVector_;
	float distance_;

private:
	Matrix4x4* viewPrpjectionMatrix_ = nullptr;
	Matrix4x4* viewportMatrix_ = nullptr;

public:
	Plane();
	Plane(const Vec3& centerPos, const Vec3& rotate, float size);
	void Draw();
	void Update();

	void SetVpVp(Matrix4x4* viewPrpjectionMatrix,Matrix4x4* viewportMatrix);
};
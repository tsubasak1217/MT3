#pragma once
#include "VectorN.h"
#include "MatrixNxN.h"
#include <stdint.h>

class Sphere{
public:

	Sphere(){};

	Sphere(
		const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection, Matrix4x4* viewport,
		uint32_t color = 0xffffffff
	);
	void Init(
		const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection, Matrix4x4* viewport,
		uint32_t color = 0xffffffff
	);

	void Draw(int kSubdivision,unsigned int color);
	void Draw(int kSubdivision);

public:
	Vec3 size_;
	Vec3 scale_;
	Vec3 rotate_;
	Vec3 translate_;
	uint32_t color_;
	float radius_;

private:
	Matrix4x4* viewPrpjectionMatrix_;
	Matrix4x4* viewportMatrix_;

public:
	void SetViewProjection(Matrix4x4* viewProjection){ viewPrpjectionMatrix_ = viewProjection; }
	void SetViewport(Matrix4x4* viewport){ viewportMatrix_ = viewport; }
};
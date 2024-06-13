#pragma once
#include "VectorN.h"
#include "MatrixNxN.h"
#include <stdint.h>

class Sphere{
public:

	Sphere() = default;

	Sphere(
		const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection = nullptr, Matrix4x4* viewport = nullptr,
		uint32_t color = 0xffffffff
	);
	void Init(
		const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection = nullptr, Matrix4x4* viewport = nullptr,
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

class EqualSphere{
public:

	EqualSphere() = default;

	EqualSphere(
		float radius, float scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection = nullptr, Matrix4x4* viewport = nullptr,
		uint32_t color = 0xffffffff
	);
	void Init(
		float radius, float scale, const Vec3& rotate, const Vec3& translate,
		Matrix4x4* viewProjection = nullptr, Matrix4x4* viewport = nullptr,
		uint32_t color = 0xffffffff
	);

	void Draw(int kSubdivision, unsigned int color);
	void Draw(int kSubdivision);

public:
	float radius_;
	float scale_;
	Vec3 rotate_;
	Vec3 translate_;
	uint32_t color_;

private:
	Matrix4x4* viewPrpjectionMatrix_;
	Matrix4x4* viewportMatrix_;

public:
	void SetViewProjection(Matrix4x4* viewProjection){ viewPrpjectionMatrix_ = viewProjection; }
	void SetViewport(Matrix4x4* viewport){ viewportMatrix_ = viewport; }
};
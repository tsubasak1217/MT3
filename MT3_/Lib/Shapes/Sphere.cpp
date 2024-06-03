#include "Sphere.h"
#include "MyFunc.h"

Sphere::Sphere(
	const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport,
	uint32_t color
){
	Init(size, scale, rotate, translate, viewProjection, viewport,color);
}

void Sphere::Init(
	const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport,
	uint32_t color
){
	size_ = size;
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;
	viewPrpjectionMatrix_ = viewProjection;
	viewportMatrix_ = viewport;
	color_ = color;
}


void Sphere::Draw(int kSubdivision, unsigned int color){

	DrawSphere(
		size_,
		scale_,
		rotate_,
		translate_,
		kSubdivision,
		*viewPrpjectionMatrix_,
		*viewportMatrix_,
		color
	);
}

void Sphere::Draw(int kSubdivision)
{
	DrawSphere(
		size_,
		scale_,
		rotate_,
		translate_,
		kSubdivision,
		*viewPrpjectionMatrix_,
		*viewportMatrix_,
		color_
	);
}

// ===============================xyzの比率が同じ純粋な球=================================

EqualSphere::EqualSphere(
	float radius, float scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport,
	uint32_t color
){
	Init(radius, scale, rotate, translate, viewProjection, viewport, color);
}

void EqualSphere::Init(
	float radius,float scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport,
	uint32_t color
){
	radius_ = radius;
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;
	viewPrpjectionMatrix_ = viewProjection;
	viewportMatrix_ = viewport;
	color_ = color;
}


void EqualSphere::Draw(int kSubdivision, unsigned int color){

	DrawSphere(
		{ radius_ * 2.0f,radius_ * 2.0f,radius_ * 2.0f },
		{ scale_,scale_,scale_ },
		rotate_,
		translate_,
		kSubdivision,
		*viewPrpjectionMatrix_,
		*viewportMatrix_,
		color
	);
}

void EqualSphere::Draw(int kSubdivision)
{
	DrawSphere(
		{ radius_ * 2.0f,radius_ * 2.0f,radius_ * 2.0f },
		{ scale_,scale_,scale_ },
		rotate_,
		translate_,
		kSubdivision,
		*viewPrpjectionMatrix_,
		*viewportMatrix_,
		color_
	);
}
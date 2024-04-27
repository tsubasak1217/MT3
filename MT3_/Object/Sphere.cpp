#include "Sphere.h"
#include "MyFunc.h"

Sphere::Sphere(
	const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport
){
	Init(size, scale, rotate, translate, viewProjection, viewport);
}

void Sphere::Init(
	const Vec3& size, const Vec3& scale, const Vec3& rotate, const Vec3& translate,
	Matrix4x4* viewProjection, Matrix4x4* viewport
){
	size_ = size;
	scale_ = scale;
	rotate_ = rotate;
	translate_ = translate;
	viewPrpjectionMatrix_ = viewProjection;
	viewportMatrix_ = viewport;
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

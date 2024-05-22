#include "Plane.h"
#include "MyFunc.h"

Plane::Plane(){}
Plane::Plane(const Vec3& centerPos, const Vec3& rotate, float size){
	centerPos_ = centerPos;
	rotate_ = rotate;
	size_ = size;
}

void Plane::SetVpVp(Matrix4x4* viewPrpjectionMatrix, Matrix4x4* viewportMatrix)
{
	viewPrpjectionMatrix_ = viewPrpjectionMatrix;
	viewportMatrix_ = viewportMatrix;
}

void Plane::Draw(){
	DrawPlane(centerPos_, rotate_, size_,*viewPrpjectionMatrix_,*viewportMatrix_);
}

void Plane::Update()
{
	normalVector_ = Normalize(Multiply({ 0.0f,-1.0f,0.0f }, RotateMatrix(rotate_)));
	distance_ = Dot(normalVector_, centerPos_);
}

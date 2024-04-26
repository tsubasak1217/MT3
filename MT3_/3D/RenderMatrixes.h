#pragma once
#include "MyFunc.h"
#include "Camera.h"

class RenderMatrixes {
public:
	RenderMatrixes(Camera* cameraPtr);
	~RenderMatrixes();
	void Init(Camera* cameraPtr);
	void Update();
	void Fin();

private:
	Camera* cameraPtr_ = nullptr;
	Matrix4x4 viewMatrix;
	float zNear;
	float zFar;
	Matrix4x4 perspectiveMatrix;
	Matrix4x4 viewProjectionMatrix;
	Matrix4x4 viewportMatrix;
	Matrix4x4 wvpVpMatrix;

public:
	void SetCameraPtr(Camera* cameraPtr) { cameraPtr_ = cameraPtr; }
	Matrix4x4 GetViewProjectionMat()const{return viewProjectionMatrix;}
	Matrix4x4 GetViewportMat()const { return viewportMatrix; }
};
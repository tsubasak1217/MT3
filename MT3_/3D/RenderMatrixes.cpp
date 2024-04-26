#include "RenderMatrixes.h"

RenderMatrixes::RenderMatrixes(Camera* cameraPtr) {
	Init(cameraPtr);
}

RenderMatrixes::~RenderMatrixes() {
}

void RenderMatrixes::Init(Camera* cameraPtr) {
	cameraPtr_ = cameraPtr;
	viewMatrix = InverseMatrix(cameraPtr_->worldMatrix_);
	zNear = 0.1f;
	zFar = 100.0f;
	perspectiveMatrix = PerspectiveMatrix(0.45f, AspectRatio(1280.0f, 720.0f), zNear, zFar);
	viewProjectionMatrix = Multiply(viewMatrix, perspectiveMatrix);
	viewportMatrix = ViewportMatrix({ 1280,720 }, { 0.0f,0.0f }, 0.0f, zFar);
	wvpVpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);
}

void RenderMatrixes::Update() {
	viewMatrix = InverseMatrix(cameraPtr_->worldMatrix_);
	viewProjectionMatrix = Multiply(viewMatrix, perspectiveMatrix);
	wvpVpMatrix = Multiply(viewProjectionMatrix, viewportMatrix);
}

void RenderMatrixes::Fin() {
}

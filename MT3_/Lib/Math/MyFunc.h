#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <memory>
#include <Novice.h>
#include <assert.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Enums.h"
#include "Easing.h"
#include "VectorN.h"
#include "MatrixNxN.h"

#include "Line.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "AABB.h"

//何もしない関数
void Void();

//================================================================
//                     ファイル操作の関数
//================================================================
std::vector<std::vector<int>>LoadFile(const std::string& csvFilePath);

//================================================================
//                       時間の関数
//================================================================
//フレーム数を時間に換算する関数
/// <summary>
/// フレーム数を時間に換算する関数
/// </summary>
/// <param name="count">:フレーム数</param>
/// <param name="tranceMode">[0:秒][1:分][2:時間]</param>
/// <returns></returns>
int FrameToClock(int count, int tranceMode);

//================================================================
//                      数学的な関数
//================================================================

//長さを計る関数
float Length(const Vec2& pos1, const Vec2& pos2);
float Length(const Vec3& pos1, const Vec3& pos2);
float Length(float pos1x, float pos1y, float pos2x, float pos2y);
float Length(const Vec2& vec);
float Length(const Vec3& vec);

//ノーマライズ関数
Vec2 Normalize(const Vec2& pos1, const Vec2& pos2);
Vec3 Normalize(const Vec3& pos1, const Vec3& pos2);
Vec2 Normalize(const Vec2& vec);
Vec3 Normalize(const Vec3& vec);

//内積を求める
float Dot(const Vec2& pos1, const Vec2& pos2, const Vec2& targetPos);
float Dot(const Vec2& a, const Vec2& b);
float Dot(const Vec3& a, const Vec3& b);

// 射影ベクトルを求める・線への最近傍点を求める
Vec3 Project(const Vec3& vector1, const Vec3& vector2);
Vec3 ClosestPoint(const Vec3& point, const Vec3& seg_origin, const Vec3& seg_end);

//外積を求める関数
float Cross(
	float line1StartX, float line1StartY,
	float line1EndX, float line1EndY,
	float targetX, float targetY
);

float Cross(Vec2 pos1, Vec2 pos2, Vec2 targetPos);

enum VIEWMODE {
	kScreen,
	kWorld
};
Vec3 Cross(Vec3 v1, Vec3 v2, bool kViewMode);


//線と線の交点を求める関数
Vec2 CrossPos(
	Vec2 line1Pos1, Vec2 line1Pos2,
	Vec2 line2Pos1, Vec2 line2Pos2
);
Vec2 CrossPos2(Vec2 line1Pos1, Vec2 line1Pos2, Vec2 line2Pos1, Vec2 line2Pos2);

//線を平行移動する関数
Vec2 ShiftLine(Vec2 pos1, Vec2 pos2, float distance);
void ShiftLineCtrl(Vec2& pos1, Vec2& pos2, float distance);

// 負数を0に変換する関数
int negaZero(int num);
float negaZero(float num);

//================================================================
//                      行列の計算関数
//================================================================

// -----------------加算------------------
Matrix2x2 Add(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Add(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Add(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

// -----------------減算------------------
Matrix2x2 Subtract(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Subtract(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Subtract(const Matrix4x4& matrix1, const Matrix4x4& matrix2);

// ---------------積を求める----------------
Vec2 Multiply(const Vec2& vector, const Matrix2x2& matrix);
Vec2 Multiply(const Vec2& vector, const Matrix3x3& matrix);
Vec3 Multiply(const Vec3& vector, const Matrix4x4& matrix);
Matrix2x2 Multiply(const Matrix2x2& matrix1, const Matrix2x2& matrix2);
Matrix3x3 Multiply(const Matrix3x3& matrix1, const Matrix3x3& matrix2);
Matrix4x4 Multiply(const Matrix4x4& matrix1, const Matrix4x4& matrix2);
// --------------スカラー倍----------------
Vec2 Multiply(const Vec2& vector, float scalar);
Vec3 Multiply(const Vec3& vector, float scalar);
Matrix2x2 Multiply(const Matrix2x2& matrix, float scalar);
Matrix3x3 Multiply(const Matrix3x3& matrix, float scalar);
Matrix4x4 Multiply(const Matrix4x4& matrix, float scalar);

// -----------------割り算------------------
Matrix2x2 Devide(const Matrix2x2& matrix, float devideNum);
Matrix3x3 Devide(const Matrix3x3& matrix, float devideNum);
Matrix4x4 Devide(const Matrix4x4& matrix, float devideNum);

// 同時座標系からデカルト座標系に変換する関数
Vec2 Transform(const Vec2& vector, const Matrix3x3& matrix);
Vec3 Transform(const Vec3& vector, const Matrix4x4& matrix);

// 単位行列を返す関数
Matrix2x2 IdentityMat2();
Matrix3x3 IdentityMat3();
Matrix4x4 IdentityMat4();

// 拡大縮小行列を作る関数
Matrix3x3 ScaleMatrix(float scaleX, float scaleY);
Matrix3x3 ScaleMatrix(const Vec2& scale);
Matrix4x4 ScaleMatrix(float scaleX, float scaleY, float scaleZ);
Matrix4x4 ScaleMatrix(const Vec3& scale);

// 回転行列を作る関数
Matrix3x3 RotateMatrix(float theta);
Matrix4x4 RotateMatrix(const Vec3& rotate);
Matrix4x4 RotateMatX(const Vec3& rotate);
Matrix4x4 RotateMatY(const Vec3& rotate);
Matrix4x4 RotateMatZ(const Vec3& rotate);

// 平行移動行列を作る関数
Matrix3x3 TranslateMatrix(float tx, float ty);
Matrix3x3 TranslateMatrix(const Vec2& t);
Matrix4x4 TranslateMatrix(float tx, float ty, float tz);
Matrix4x4 TranslateMatrix(const Vec3& t);

// アフィン変換行列を作る関数
Matrix3x3 AffineMatrix(Vec2 scale, float rotateTheta, Vec2 transLate);
Matrix4x4 AffineMatrix(const Vec3& scale, const Vec3& rotate, const Vec3& translate);

//逆行列を求める関数
Matrix2x2 InverseMatrix(const Matrix2x2& matrix);
Matrix3x3 InverseMatrix(const Matrix3x3& matrix);
Matrix4x4 InverseMatrix(const Matrix4x4& matrix);

//転置行列を求める関数
Matrix2x2 Transpose(const Matrix2x2& matrix);
Matrix3x3 Transpose(const Matrix3x3& matrix);
Matrix4x4 Transpose(const Matrix4x4& matrix);

//正射影行列を求める関数
Matrix3x3 OrthoMatrix(float left, float right, float top, float bottom);
Matrix4x4 OrthoMatrix(float left, float right, float top, float bottom, float znear, float zfar);

// 透視投影行列(視錐台)を求める関数
float AspectRatio(float windowWidth, float windowHeight);
Matrix4x4 PerspectiveMatrix(float fovY, float aspectRatio, float znear, float zfar);

//ビューポート変換行列を求める関数
Matrix3x3 ViewportMatrix(const Vec2& size, const Vec2& LeftTop);
Matrix4x4 ViewportMatrix(const Vec2& size, const Vec2& LeftTop, float minDepth, float maxDepth);

//レンダリングパイプライン作る関数
Matrix3x3 WvpVpMatrix(
	Vec2 playerPos, Vec2 playerScale, float playerAngle,
	Vec2 cameraPos, Vec2 cameraScale, float cameraAngle,
	Vec2 cameraRange, Vec2 leftTop,
	Vec2 screenSize
);

//行列の情報を表示する関数
void MatrixScreenPrintf(int posX, int posY, const Matrix2x2& matrix, const char* string = 0);
void MatrixScreenPrintf(int posX, int posY, const Matrix3x3& matrix, const char* string = 0);
void MatrixScreenPrintf(int posX, int posY, const Matrix4x4& matrix, const char* string = 0);
void VecScreenPrintf(int posX, int posY, const Vec2& vector, const char* string = 0);
void VecScreenPrintf(int posX, int posY, const Vec3& vector, const char* string = 0);

//================================================================
//                     当たり判定関数
//================================================================

//回転していない矩形と円の当たり判定
bool IsHitBox_Ball(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius);
//回転していない矩形と円の当たり判定(当たった面を返す)
int IsHitBox_BallDirection(Vec2 boxCenter, Vec2 ballPos, Vec2 boxSize, float ballRasius);
// 自由な球同士の当たり判定
bool Collision_Sphere_Sphere(Sphere sphere1, Sphere sphere2);
// 球と平面の当たり判定
bool Collision_Sphere_Plane(const Sphere& sphere, const Plane& plane);
// 線分と平面の当たり判定
bool Collision_Plane_Line(const Plane& plane, const Line& line);
// 三角形と線の当たり判定
bool Collision_Triangle_Line(const Triangle& triangle, const Line& line);
// AABB同士の当たり判定
bool Collision_AABB_AABB(const AABB& aabb1, const AABB& aabb2);

//================================================================
//                     オリジナル描画関数
//================================================================
namespace My {

	//中心基準矩形
	void DrawQuad(
		Vec2 center,
		Vec2 size,
		int drawPosX, int drawPosY,
		int drawWidth, int drawHight,
		float scaleX, float scaleY,
		int GH, float theta, int color
	);
	//中心座標基準三角
	void DrawTriangle(Vec2 center, float radius, float theta, int color);
	void DrawTriangleWire(Vec2 center, float radius, float theta, int color);
	//線
	void DrawLine(const Vec2& pos1, const Vec2& pos2, int color);
	//星
	void DrawStar(Vec2 center, float radius, Vec2 scale, float theta, int color);
	void DrawStarWire(Vec2 center, float radius, Vec2 scale, float theta, int color);
	//キラキラ関数
	void DrawTwinkle(Vec2 center, Vec2 size, float theta, int color, float fatLevel);
	//雪を描く関数
	void DrawSnow(Vec2 center, Vec2 size, float theta, int color, float fatLevel);
}

void DrawGrid(Matrix4x4* viewPjojectionMatrix, Matrix4x4* viewportMatrix);

// 球を描画する関数
void DrawSphere(
	const Vec3& size,
	const Vec3& scale,
	const Vec3& rotate,
	const Vec3& translate,
	int kSubdivision,
	const Matrix4x4& viewPjojectionMatrix, const Matrix4x4& viewportMatrix,
	unsigned int color
);

// 平面を描画する関数
void DrawPlane(
	const Vec3& centerPos,
	const Vec3& rotate,
	float size,
	Matrix4x4 viewProjectionMat,
	Matrix4x4 viewportMat
);

// 三角平面を描画する関数
void DrawTrianglePlane(
	const Triangle& triangle,
	Matrix4x4 viewProjectionMat,
	Matrix4x4 viewportMat
);

void DrawHitPos_Plane_Line(
	const Vec3& normal,
	const Vec3& point,
	const Line& line,
	Matrix4x4 viewProjectionMat,
	Matrix4x4 viewportMat
);

// 線を描画する関数
void DrawSegment(
	const Line& seg,
	const Matrix4x4& viewPjojectionMatrix,
	const Matrix4x4& viewportMatrix,
	uint32_t color
);

// AABBを描画する関数
void DrawAABB(
	const AABB& aabb,
	const Matrix4x4& viewPjojectionMatrix,
	const Matrix4x4& viewportMatrix,
	uint32_t color
);

//================================================================
//                     色を扱う関数
//================================================================

//色の各成分を求める関数
int Red(int color);
int Green(int color);
int Blue(int color);
int Alpha(int color);

//色を変える関数
int ChangeColor(int startColor, int aimColor, float divideNum, float rate);
int ChangeColorT(int startColor, int aimColor, float t);

int GrayScale(int color);

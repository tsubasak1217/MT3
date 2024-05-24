#pragma once
#include "VectorN.h"

struct Triangle{
	
public:
	Vec3 vertex_[3];
	int color_;

public:
	Triangle(){
		color_ = 0xffffffff;
	};

	Triangle(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3,int color = 0xffffffff){
		vertex_[0] = vertex1;
		vertex_[1] = vertex2;
		vertex_[2] = vertex3;
		color_ = color;
	}

	void Init(const Vec3& vertex1, const Vec3& vertex2, const Vec3& vertex3, int color = 0xffffffff){
		vertex_[0] = vertex1;
		vertex_[1] = vertex2;
		vertex_[2] = vertex3;
		color_ = color;
	}
};

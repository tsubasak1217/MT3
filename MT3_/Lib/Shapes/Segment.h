#pragma once
#include "VectorN.h"

struct Segment
{
	Vec3 origin_;
	Vec3 end_;

	Segment(){};
	Segment(const Vec3& origin, const Vec3& end){
		origin_ = origin;
		end_ = end;
	}
};
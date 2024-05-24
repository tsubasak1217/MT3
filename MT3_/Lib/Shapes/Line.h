#pragma once
#include "VectorN.h"
#include "Enums.h"
#include <stdint.h>

struct Line
{
	Vec3 origin_;
	Vec3 end_;
	uint32_t color_;
	int type_;

	Line(){};
	Line(const Vec3& origin, const Vec3& end, int type = SEGMENT,uint32_t color = 0xffffff){
		origin_ = origin;
		end_ = end;
		type_ = type;
		color_ = color;
	}

	void Init(const Vec3& origin, const Vec3& end, int type = SEGMENT, uint32_t color = 0xffffff){
		origin_ = origin;
		end_ = end;
		type_ = type;
		color_ = color;
	}
};
#pragma once
#include "VectorN.h"
#include <stdint.h>

struct AABB{

	AABB() = default;
	AABB(const Vec3& point1, const Vec3& point2,uint32_t color = 0xffffffff);

	void UpdateMinMax();

	Vec3 point[2];
	Ptr3 min;
	Ptr3 max;
	uint32_t color;
};
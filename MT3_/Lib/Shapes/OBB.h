#pragma once
#include "VectorN.h"
#include "AABB.h"
#include <stdint.h>

struct OBB{

	OBB() = default;
	OBB(const Vec3& center, const Vec3& rotate, const Vec3& size, uint32_t color = 0xffffffff);

	Vec3 center;
	Vec3 rotate;
	Vec3 size;
	uint32_t color;
};
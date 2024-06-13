#include "OBB.h"

OBB::OBB(const Vec3& center, const Vec3& rotate, const Vec3& size, uint32_t color)
{
	this->center = center;
	this->rotate = rotate;
	this->size = size;
	this->color = color;
}

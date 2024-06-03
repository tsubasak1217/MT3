#include "AABB.h"

AABB::AABB(const Vec3& point1, const Vec3& point2, uint32_t color){
	point[0] = point1;
	point[1] = point2;
	this->color = color;;
	UpdateMinMax();
}

void AABB::UpdateMinMax(){

	if(point[0].x <= point[1].x){
		min.x = &point[0].x;
		max.x = &point[1].x;
	} else{
		min.x = &point[1].x;
		max.x = &point[0].x;
	}

	if(point[0].y <= point[1].y){
		min.y = &point[0].y;
		max.y = &point[1].y;
	} else{
		min.y = &point[1].y;
		max.y = &point[0].y;
	}

	if(point[0].z <= point[1].z){
		min.z = &point[0].z;
		max.z = &point[1].z;
	} else{
		min.z = &point[1].z;
		max.z = &point[0].z;
	}
}

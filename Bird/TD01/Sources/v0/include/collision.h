#ifndef COLLISION_IS_DEF
#define COLLISION_IS_DEF

#include <math.h>
#include "object.h"


int testCollisionBetweenTwoObjects(dynamic_object_t* object_1, dynamic_object_t* object_2);
float distanceBetweenTwoPoints(point_t a, point_t b);

#endif
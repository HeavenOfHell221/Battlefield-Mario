#ifndef BADBIRD_IS_DEF
#define BADBIRD_IS_DEF

#include <math.h>
#include "object.h"
#include "action.h"
#include "timer.h"
#include "debug.h"
#include "error.h"
#include "animation.h"
#include "constants.h"
#include "collision.h"


void animation_badbird_add (int x, int y, float amplitude, float period, int speed, int offset);
int animation_badbird_onestep(dynamic_object_t* object);
void badbird_animation(dynamic_object_t* object);
void birdDetection(dynamic_object_t* bird, dynamic_object_t* object2);

#endif
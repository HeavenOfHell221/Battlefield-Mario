#ifndef MISSILE_IS_DEF
#define MISSILE_IS_DEF

#include <SDL.h>
#include "object.h"
#include "debug.h"
#include "animation.h"
#include "action.h"
#include "collision.h"

void animation_missile_add (dynamic_object_t *obj, int direction);
int animation_missile_onestep (dynamic_object_t *obj);

void apply_motion_missile(dynamic_object_t* object);
void apply_animation_missile(dynamic_object_t* object);
void apply_detection_missile(dynamic_object_t* object);

#endif
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
void badbirdDetection(dynamic_object_t *object);

#endif
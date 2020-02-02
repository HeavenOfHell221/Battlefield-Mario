#ifndef EXPLOSION_IS_DEF
#define EXPLOSION_IS_DEF

#include "object.h"
#include "sprite.h"
#include "debug.h"
#include "bird.h"
#include "animation.h"
#include "debug.h"
#include "action.h"

void createExplosion(dynamic_object_t *object);
void animation_explosion_add (dynamic_object_t *object, int x_offset, int y_offset);
int animation_explosion_onestep (dynamic_object_t *object);

#endif
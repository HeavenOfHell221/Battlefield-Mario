#include <SDL_image.h>
#include <stdint.h>
#include "constants.h"
#include "object.h"
#include "bird.h"
#include "missile.h"
#include "explosion.h"
#include "timer.h"
#include "action.h"

object_type_t object_class[5];

void object_init ()
{ 
    object_class[OBJECT_TYPE_BIRD].animate_func = animation_bird_onestep;
    object_class[OBJECT_TYPE_MISSILE].animate_func = animation_missile_onestep;
    object_class[OBJECT_TYPE_EXPLOSION].animate_func = animation_explosion_onestep;
    object_class[OBJECT_TYPE_BADBIRD].animate_func = animation_badbird_onestep;
    object_class[OBJECT_TYPE_TEXT].animate_func = NULL;

    object_class[OBJECT_TYPE_BIRD].timer_func = timer_bird;
    object_class[OBJECT_TYPE_MISSILE].timer_func = NULL;
    object_class[OBJECT_TYPE_EXPLOSION].timer_func = NULL;
    object_class[OBJECT_TYPE_BADBIRD].timer_func = NULL;
    object_class[OBJECT_TYPE_TEXT].timer_func = NULL;
}

void object_object_init(dynamic_object_t *object, sprite_t *sp, int type, int state, int x, int y, float xs, float ys, int direction, int animation_status)
{
    object->sprite = sp;
    object->type = type;
    object->state = state;
    object->position.x = x;
    object->position.y = y;
    object->xs = xs;
    object->ys = ys;
    object->direction = direction;
    object->current_animation = 0;
    object->animation_status = animation_status;
    object->global_chain.next = NULL;
    object->global_chain.prev = NULL;
    action_init(&object->nextAnimationStep);
    actionTab_init(object->actions);
    timer_init(&object->timer);
    setSinus(&object->sin, 0, 0, 0);
}

void setSinus(sinus_t* sin, float amplitude, float period, int offset)
{
    sin->i = offset;
    sin->amplitude = amplitude;
    sin->period = period;
}


#include "badbird.h"

enum  {
    keyboardOff = 0
};

void animation_badbird_add (int x, int y, float amplitude, float period, int speed, int offset)
{
    dynamic_object_t* badBird = (dynamic_object_t*) calloc(1, sizeof(dynamic_object_t));
    object_object_init(badBird, &badBird_sprite, OBJECT_TYPE_BADBIRD, OBJECT_STATE_IN_AIR, 0, 0, speed, 0, LEFT, NORMAL_DIRECTION);
    setActionCooldown(&badBird->nextAnimationStep, 20);
    badBird->position.x = x;
    badBird->position.y = y;
    setSinus(&badBird->sin, amplitude, period, offset);

    animation_mobile_object_add(badBird);
}

int animation_badbird_onestep(dynamic_object_t* object)
{
    object->position.x -= (object->xs + bird_obj.xs);    

    if(object->position.y > WIN_HEIGHT - object->sprite->display_height)
        object->position.y = WIN_HEIGHT - object->sprite->display_height;    

    object->sin.i += object->sin.amplitude;
    
    if(object->sin.i  > M_PI * 2)
        object->sin.i  = 0;

    object->position.y += (int) (sin(object->sin.i) * object->sin.period);

    if (object->position.y <= 0)
    {
        object->ys = 0;
        object->position.y = 0;
    }

    if(object->position.x <= (0 - object->sprite->display_height))
    {
        object->state = OBJECT_STATE_DESTROYED;
    }

    badbird_animation(object);
        
    return object->state;
}

void badbird_animation(dynamic_object_t* object)
{
    if (object->sprite->is_animation_reversed)
    {
        if (object->current_animation == 0)
        object->animation_status = NORMAL_DIRECTION;
        if (object->current_animation == object->sprite->animation_steps_number)
        object->animation_status = REVERSED_DIRECTION;
        if (isPossibleAction(&object->nextAnimationStep))
        object->current_animation = object->current_animation + object->animation_status;
    }
    else
    {
        if (isPossibleAction(&object->nextAnimationStep))
        object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
    }
}

void birdDetection(dynamic_object_t* bird, dynamic_object_t* object)
{
    if(testCollisionBetweenTwoObjects(bird, object) == 1 && bird->state != OBJECT_STATE_DEAD)
    {
        timer_func_t func = object_class[bird->type].timer_func;
        if (func != NULL)
        {
            func(bird);
        }  
    }
}
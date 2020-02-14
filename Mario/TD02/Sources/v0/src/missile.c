#include "missile.h"

enum {
    nextAnimationStep = 0
};


void animation_missile_add (dynamic_object_t *object, int direction)
{
    dynamic_object_t* missile = (dynamic_object_t*) calloc(1, sizeof(dynamic_object_t));

    object_object_init(missile, &missile_sprite, OBJECT_TYPE_MISSILE, OBJECT_STATE_IN_AIR, 0, 0, 8, direction, NORMAL_DIRECTION);
    missile->positionScreen.x = object->positionScreen.x;
    missile->positionScreen.y = object->positionScreen.y;

    action_init_init(missile, nextAnimationStep, 0);

    animation_mobile_object_add(missile);
}

int animation_missile_onestep (dynamic_object_t *object)
{
    if(object->direction == RIGHT)
    {
        object->xs = object->speed;
    }
    else
    {
        object->xs = -object->speed;
    }
    
    object->positionScreen.x += object->xs;
    object->positionMap.x += object->xs;

    if(object->positionScreen.x > WIN_WIDTH * 1.1 || object->positionScreen.x < WIN_HEIGHT * -0.1)
        return OBJECT_STATE_DESTROYED;

    if(isPossibleAction(&object->nextAnimationStep))
    {
        object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
    }

    return object->state;
}

void badbirdDetection(dynamic_object_t *missile)
{
    /*for_all_objects(object)
    {
        if(object->type == OBJECT_TYPE_BADBIRD)
        {
            if(testCollisionBetweenTwoObjects(missile, object) == 1)
            {
                missile->state = OBJECT_STATE_DESTROYED;
                object->state = OBJECT_STATE_DESTROYED;
                createExplosion(object);
            }
        }
    }*/
}

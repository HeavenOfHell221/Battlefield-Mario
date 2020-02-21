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
    missile->positionMap.x = object->positionMap.x;
    missile->positionMap.y = object->positionMap.y;

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
    apply_detection_missile(object);
    apply_motion_missile(object);
    apply_animation_missile(object);
    

    return object->state;
}

void apply_motion_missile(dynamic_object_t* object)
{
    object->positionScreen.x += object->xs;
    object->positionMap.x += object->xs;
}

void apply_animation_missile(dynamic_object_t* object)
{
    if(isPossibleAction(&object->nextAnimationStep))
    {
        object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
    }
}

void apply_detection_missile(dynamic_object_t* object)
{
    if(object->xs > 0) // Vers la droite
    {
        int bloc1 = map_get((object->positionMap.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionMap.y + 1) / MAP_PIXEL);
        int bloc2 = map_get((object->positionMap.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get((object->positionMap.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            createExplosion(object);
            object->state = OBJECT_STATE_DESTROYED;
        }
    }
    else if(object->xs < 0) // Vers la gauche
    {
        int bloc1 = map_get((object->positionMap.x + object->xs) / MAP_PIXEL, (object->positionMap.y + 1) / MAP_PIXEL);
        int bloc2 = map_get((object->positionMap.x + object->xs) / MAP_PIXEL, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get((object->positionMap.x + object->xs) / MAP_PIXEL, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            createExplosion(object);
            object->state = OBJECT_STATE_DESTROYED;
        }
    }
}
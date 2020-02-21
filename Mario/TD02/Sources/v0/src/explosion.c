#include "explosion.h"

void animation_explosion_add (dynamic_object_t *object, int x_offset, int y_offset)
{
    object->positionMap.x = x_offset;
    object->positionMap.y = y_offset;

    animation_mobile_object_add(object);
}

void createExplosion(dynamic_object_t *object)
{
    dynamic_object_t* explosion = (dynamic_object_t*) calloc(1, sizeof(dynamic_object_t));

    object_object_init(explosion, &explosion_sprite, OBJECT_TYPE_EXPLOSION, OBJECT_STATE_IN_AIR, 0, 0, 8, RIGHT, NORMAL_DIRECTION);

    animation_explosion_add(explosion, object->positionMap.x - object->sprite->display_width, object->positionMap.y - (object->sprite->display_height/2));
}

int animation_explosion_onestep (dynamic_object_t *object)
{
    if(object->current_animation == object->sprite->images_number - 1)
        return OBJECT_STATE_DESTROYED;


    if(isPossibleAction(&object->nextAnimationStep))
    {
        object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
    }

    return object->state;
}
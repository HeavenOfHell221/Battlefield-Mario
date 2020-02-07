#include "animation.h"

list_head_t all_objects_dyn;
list_head_t all_objects_static;

void animation_mobile_object_add (dynamic_object_t *object)
{
    list_add_tail(&object->global_chain, &all_objects_dyn);
}

void animation_mobile_object_del (dynamic_object_t *object)
{
    list_del(&object->global_chain);
}

void animation_static_object_add (static_object_t *object)
{
    list_add_tail(&object->global_chain, &all_objects_static);
}

void animation_static_object_del (static_object_t *object)
{
    list_del(&object->global_chain);
}

void animation_clean()
{
    for_all_objects_dyn(object)
    {
        if(object != &mario_object)
            animation_clean_one(object);
    }
}

void animation_init ()
{
    INIT_LIST_HEAD(&all_objects_dyn);
    INIT_LIST_HEAD(&all_objects_static);
    createMario();
    animation_mobile_object_add(&mario_object);
}

void animation_one_step (int left, int right, int up, int down, int espace)
{
    animation_mario_moves(&mario_object, left, right, up, espace);

    for_all_objects_dyn(currentObject)
    {
        animate_func_t func = object_class[currentObject->type].animate_func;
        if (func != NULL)
        {
            int state = func(currentObject);

            switch(state)
            {
                case OBJECT_STATE_DESTROYED:
                    animation_clean_one(currentObject);
                    break;
                default:
                    break;
            }
        }
    }

}

void animation_render_objects()
{
    for_all_objects_static(currentObject)
    {
        SDL_Rect dst;
        dst.x = currentObject->positionMap.x - positionScreenWorld.x;
        dst.y = currentObject->positionMap.y - positionScreenWorld.y;
        dst.w = currentObject->sprite->display_width;
        dst.h = currentObject->sprite->display_height;

        SDL_RenderCopy (ren, currentObject->sprite->texture, NULL, &dst);
    }
    
    for_all_objects_dyn(currentObject)
    {
        graphics_render_object(currentObject);
    }

    
}

void animation_clean_one(dynamic_object_t *object)
{
    animation_mobile_object_del(object);
    free(object);
}
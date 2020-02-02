#include "animation.h"

list_head_t all_objects;

void animation_mobile_object_add (dynamic_object_t *object)
{
    list_add_tail(&object->global_chain, &all_objects);
}

void animation_mobile_object_del (dynamic_object_t *object)
{
    list_del(&object->global_chain);
}

void animation_clean()
{
    for_all_objects(object)
    {
        if(object != &bird_obj)
            animation_clean_one(object);
    }
}

void animation_init ()
{
    INIT_LIST_HEAD(&all_objects);
    createBird();
    animation_mobile_object_add(&bird_obj);
}

void animation_one_step (int left, int right, int up, int down, int espace)
{
    animation_bird_moves(&bird_obj, up, down, espace);

    for_all_objects(currentObject)
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
        else
            continue;

        switch(currentObject->type)
        {
            case OBJECT_TYPE_MISSILE:
                badbirdDetection(currentObject);
                break;
            case OBJECT_TYPE_BADBIRD:
                birdDetection(&bird_obj, currentObject);
                break;
            default:
                break;
        }   
    }
}

void animation_render_objects()
{
    for_all_objects(object)
        graphics_render_object(object);
}

void animation_clean_one(dynamic_object_t *object)
{
    animation_mobile_object_del(object);
    free(object);
}
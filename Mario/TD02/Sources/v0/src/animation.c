#include "animation.h"

list_head_t all_objects_dyn;

void animation_mobile_object_add (dynamic_object_t *object)
{
    list_add_tail(&object->global_chain, &all_objects_dyn);
}

void animation_mobile_object_del (dynamic_object_t *object)
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
    createMario();
    animation_mobile_object_add(&mario_object);
}

void animation_one_step (int left, int right, int up, int down, int espace, int tab)
{
    if(GAMEMODE == GAMEMODE_INGAME)
    {
        animation_mario_moves(&mario_object, left, right, up, espace);
    }
    else if(GAMEMODE == GAMEMODE_EDITOR)
    {
        animation_mario_moves(&mario_object, 0, 0, 0, 0);
        animation_cursor_moves(&editorCursor, left, right, up, down, espace, tab);
    }
   
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
    for(int x = 0; x < MAP_SIZE_X; x++)
    {
        for(int y = 0; y < MAP_SIZE_Y; y++)
        {
            int map_type = map_get(x, y);
            if(map_type != OBJECT_AIR)
            {
                graphics_render_object_static(&map_objects[map_type], x * MAP_PIXEL, y * MAP_PIXEL);
            }
        }
    } 
    
    if(GAMEMODE == GAMEMODE_EDITOR)
    {
        graphics_render_object_static(&editorCursor.cursorLight, editorCursor.position.x * MAP_PIXEL - 16, editorCursor.position.y * MAP_PIXEL - 16);
        graphics_render_object_static(&map_objects[editorCursor.currentBlock], editorCursor.position.x * MAP_PIXEL , editorCursor.position.y * MAP_PIXEL);
    }
    
    map_objects[OBJECT_COIN].current_animation = (map_objects[OBJECT_COIN].current_animation + map_objects[OBJECT_COIN].animation_status) % map_objects[OBJECT_COIN].sprite->images_number;
    
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
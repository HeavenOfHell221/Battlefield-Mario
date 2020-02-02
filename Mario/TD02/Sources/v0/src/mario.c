#include "mario.h"

enum {
    shotMissile = 0,
    blinkTexture = 1
};

dynamic_object_t mario_object;

void createMario()
{
    object_object_init(&mario_object, &mario_sprite, OBJECT_TYPE_MARIO, OBJECT_STATE_IN_AIR, 100, 100, 4, 0, LEFT, NORMAL_DIRECTION);
    action_init_init(&mario_object, shotMissile, SHOT_MISSILE_DELAY);
}

void animation_mario_moves(dynamic_object_t* object, int left, int right, int up, int espace)
{
    if(left && !right)
    {
        object->nextAnimationStep.currentState = 0;
        object->direction = LEFT;
        object->xs = -4;
    }
    else if(right && !left)
    {
        object->nextAnimationStep.currentState = 0;
        object->direction = RIGHT;
        object->xs = 4;
    }
    else
    {
        object->nextAnimationStep.currentState = 1;
        object->xs = 0;
    }

    if(up && object->state == OBJECT_STATE_GROUND)
    {
        object->state = OBJECT_STATE_IN_AIR;
        object->ys = JUMP_FORCE;
    }

    if(espace)
    {
        if(isPossibleAction(&object->actions[shotMissile]))
        {
            animation_missile_add(object, object->direction);
        }
    }
}

int animation_mario_onestep(dynamic_object_t* object)
{
    object->state = OBJECT_STATE_IN_AIR;
    apply_gravity(object);
    apply_detection_bloc_solid_X(object);
    apply_detection_bloc_solid_Y(object);
    apply_motion(object);
    apply_animation(object);
    printDebug(object);

    return object->state;
}

void apply_gravity(dynamic_object_t* object)
{
    if (object->ys < MAX_GRAVITY && object->state == OBJECT_STATE_IN_AIR)
        object->ys += GRAVITY;
}

void apply_motion(dynamic_object_t* object)
{
    object->positionScreen.y += object->ys;
    object->positionOffset.y += object->ys;
    object->positionScreen.x += object->xs;
    object->positionOffset.x += object->xs;
}


void apply_animation(dynamic_object_t* object)
{
    if(isPossibleAction(&object->nextAnimationStep) && object->nextAnimationStep.currentState == 0)
    {
        object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
    }
}

void apply_detection_bloc_solid_X(dynamic_object_t* object)
{
    if(object->xs > 0) // Vers la droite
    {
        int bloc1 = map_get((object->positionOffset.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionOffset.y + 1) / MAP_PIXEL);
        int bloc2 = map_get((object->positionOffset.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionOffset.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get((object->positionOffset.x + object->xs + object->sprite->display_width) / MAP_PIXEL, (object->positionOffset.y + object->sprite->display_height) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID 
        || get_type(bloc2) == MAP_OBJECT_SOLID
        || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            object->xs = 0;
        }
    }
    else if(object->xs < 0) // Vers la gauche
    {
        int bloc1 = map_get((object->positionOffset.x + object->xs) / MAP_PIXEL, (object->positionOffset.y + 1) / MAP_PIXEL);
        int bloc2 = map_get((object->positionOffset.x + object->xs) / MAP_PIXEL, (object->positionOffset.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get((object->positionOffset.x + object->xs) / MAP_PIXEL, (object->positionOffset.y + object->sprite->display_height) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID 
        || get_type(bloc2) == MAP_OBJECT_SOLID
        || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            object->xs = 0;
        }
    }
}

void apply_detection_bloc_solid_Y(dynamic_object_t* object)
{
    if(object->ys > 0) // Vers le bas
    {
        int bloc1 = map_get((object->positionOffset.x + 5) / MAP_PIXEL, (object->positionOffset.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        int bloc2 = map_get((object->positionOffset.x + object->sprite->display_width - 5) / MAP_PIXEL, (object->positionOffset.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID
        || get_type(bloc1) == MAP_OBJECT_SEMI_SOLID || get_type(bloc2) == MAP_OBJECT_SEMI_SOLID)
        {
            object->ys = 0;
            object->state = OBJECT_STATE_GROUND;
        }
    }
    else if(object->ys < 0) // Vers le haut
    {
        int bloc1 = map_get((object->positionOffset.x + 5) / MAP_PIXEL, (object->positionOffset.y + object->ys/2) / MAP_PIXEL);
        int bloc2 = map_get((object->positionOffset.x + object->sprite->display_width - 5) / MAP_PIXEL, (object->positionOffset.y + object->ys/2) / MAP_PIXEL);
        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID)
        {
            object->ys = 0;
            object->state = OBJECT_STATE_GROUND;
        }
    }
}

void printDebug(dynamic_object_t* object)
{
    if(object->state == OBJECT_STATE_IN_AIR)
    {
        printf("State => AIR\n");
    }
    else if(object->state == OBJECT_STATE_GROUND)
    {
        printf("State =>  GROUND\n");
    }  

    printf("positionScreen => %d, %d\n", object->positionScreen.x, object->positionScreen.y);
    printf("positionOffset => %d, %d\n", object->positionOffset.x, object->positionOffset.y);
    printf("Speed => %f, %f\n", object->xs, object->ys);
    printf("Bloc => %d\n\n", get_type(map_get((object->positionOffset.x + 5) / MAP_PIXEL, (object->positionOffset.y + object->sprite->display_height - 1) / MAP_PIXEL)));
}










































































/*void apply_block_detection_y(dynamic_object_t* object, int bloc_type)
{
    int map_type = map_get((object->positionOffset.x + MAP_PIXEL / 2) / MAP_PIXEL, (object->positionOffset.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
    if(map_type == bloc_type)
    {
        int map_type_test = map_get((object->positionOffset.x + MAP_PIXEL / 2) / MAP_PIXEL, (object->positionOffset.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        while(map_type_test == bloc_type)
        {
            object->ys--;
            map_type_test = map_get((object->positionOffset.x + MAP_PIXEL / 2) / MAP_PIXEL, (object->positionOffset.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        }
        object->state = OBJECT_STATE_GROUND;
    }
}*/

/*void apply_block_detection_x(dynamic_object_t* object, int bloc_type)
{
    if(object->direction == LEFT)
    {
        int map_type = map_get((object->positionScreen.x + object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
        if(map_type == bloc_type)
        {
            int map_type_test = map_get((object->positionScreen.x+ object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
            while(map_type_test == bloc_type)
            {  
                object->xs++;
                map_type_test = map_get((object->positionScreen.x+ object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
            }
        }
    }
    else if(object->direction == RIGHT)
    {
        int map_type = map_get((object->positionScreen.x + object->sprite->display_width + object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
        if(map_type == bloc_type)
        {
            int map_type_test = map_get((object->positionScreen.x + object->sprite->display_width + object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
            while(map_type_test == bloc_type)
            {  
                object->xs--;
                map_type_test = map_get((object->positionScreen.x + object->sprite->display_width + object->xs) / MAP_PIXEL, object->positionScreen.y / MAP_PIXEL);
            }
        }
    }
}*/
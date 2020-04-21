#include "mario.h"

enum {
    shotMissile = 0,
    blinkTexture = 1
};

dynamic_object_t mario_object;

void createMario()
{
    object_object_init(&mario_object, &mario_sprite, OBJECT_TYPE_MARIO, OBJECT_STATE_IN_AIR, WIN_WIDTH * 0.25, WIN_HEIGHT * 0.25, 4, LEFT, NORMAL_DIRECTION);
    action_init_init(&mario_object, shotMissile, SHOT_MISSILE_DELAY);
    GAMEMODE = GAMEMODE_INGAME;
}

void animation_mario_moves(dynamic_object_t* object, int left, int right, int up, int espace)
{
    if(left && !right)
    {
        object->nextAnimationStep.currentState = 0;
        object->direction = LEFT;
        object->xs = -object->speed;
    }
    else if(right && !left)
    {
        object->nextAnimationStep.currentState = 0;
        object->direction = RIGHT;
        object->xs = object->speed;
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
    apply_detection(object);
    apply_max_edge(object);
    apply_motion(object);
    apply_animation(object);
    //printDebug(object);

    return object->state;
}

void apply_max_edge(dynamic_object_t* object)
{
    apply_max_edge_X(object);
    apply_max_edge_Y(object);
}

void apply_max_edge_Y(dynamic_object_t* object)
{
    if(object->positionScreen.y > WIN_HEIGHT * 0.6)
    {
        if(positionScreenWorld.y + WIN_HEIGHT < MAP_SIZE_Y * MAP_PIXEL)
        {
            object->positionScreen.y = WIN_HEIGHT * 0.6;
            positionScreenWorld.y += object->ys;
        }
        else
        {
            while((positionScreenWorld.y % MAP_PIXEL) != 0 && positionScreenWorld.y > 0)
            {
                positionScreenWorld.y--;
                object->positionMap.y--;
            }

            while((object->positionMap.y - object->positionScreen.y) % MAP_PIXEL != 0)
            {
                object->positionMap.y++;
            }
        }
    }
    else if(object->positionScreen.y < WIN_HEIGHT * 0.4)
    {
        if(positionScreenWorld.y != 0)
        {
            object->positionScreen.y = WIN_HEIGHT * 0.4;
            positionScreenWorld.y += object->ys;

            if(positionScreenWorld.y < 0)
            {
                positionScreenWorld.y = 0;
            }
        }
    }
}

void apply_max_edge_X(dynamic_object_t* object)
{
    object->canMoveTrees = 0;
    if(object->positionScreen.x > WIN_WIDTH * 0.8)
    {
        if(positionScreenWorld.x + WIN_WIDTH < MAP_SIZE_X * MAP_PIXEL)
        {
            object->positionScreen.x = WIN_WIDTH * 0.8 + 1;
            positionScreenWorld.x += object->xs;
            object->canMoveTrees = 1;
        }
    }
    else if(object->positionScreen.x < WIN_WIDTH * 0.2)
    {
        if(positionScreenWorld.x != 0)
        {
            object->positionScreen.x = WIN_WIDTH * 0.2 - 1;
            positionScreenWorld.x += object->xs;
            object->canMoveTrees = 1;
            if(positionScreenWorld.x < 0)
            {
                positionScreenWorld.x = 0;
            }
        }
    }
}

void apply_detection(dynamic_object_t* object)
{
    apply_detection_bloc_solid_X(object);
    apply_detection_bloc_solid_Y(object);
}

void apply_gravity(dynamic_object_t* object)
{
    if (object->ys < MAX_GRAVITY && object->state == OBJECT_STATE_IN_AIR)
    {
        object->ys += GRAVITY;
    }
}

void apply_motion(dynamic_object_t* object)
{
    object->positionScreen.y += object->ys;
    object->positionMap.y += object->ys;
    object->positionScreen.x += object->xs;
    object->positionMap.x += object->xs;

    if(positionScreenWorld.x == 0)
    {
        object->positionMap.x = object->positionScreen.x;
    }

    if(positionScreenWorld.y == 0)
    {
        object->positionMap.y = object->positionScreen.y;
    }

    if(object->positionMap.y < 0)
    {
        object->positionMap.y = 0;
        object->ys = 0;
    }

    if(object->positionScreen.y < 0)
    {   
        object->positionScreen.y = 0;
        object->ys = 0;
    }
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
        int x = (object->positionMap.x + object->xs + object->sprite->display_width) / MAP_PIXEL;

        int bloc1 = map_get(x, (object->positionMap.y + 1) / MAP_PIXEL);
        int bloc2 = map_get(x, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get(x, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);
        
        if(get_type(bloc2) == MAP_OBJECT_COLLECTIBLE)
        {
            map_set(OBJECT_AIR, x, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        }

        if(get_type(bloc3) == MAP_OBJECT_COLLECTIBLE)
        {
            map_set(OBJECT_AIR, x, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);
        }
        
        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            object->xs = 0;
        }
    }
    else if(object->xs < 0) // Vers la gauche
    {
        int x = (object->positionMap.x + object->xs) / MAP_PIXEL;
        int bloc1 = map_get(x, (object->positionMap.y + 1) / MAP_PIXEL);
        int bloc2 = map_get(x, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        int bloc3 = map_get(x, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);

        if(get_type(bloc2) == MAP_OBJECT_COLLECTIBLE)
        {
            map_set(OBJECT_AIR, x, (object->positionMap.y + 1 + object->sprite->display_height / 2) / MAP_PIXEL);
        }

        if(get_type(bloc3) == MAP_OBJECT_COLLECTIBLE)
        {
            map_set(OBJECT_AIR, x, (object->positionMap.y + object->sprite->display_height) / MAP_PIXEL);
        }

        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID || get_type(bloc3) == MAP_OBJECT_SOLID)
        {
            object->xs = 0;
        }
    }
}

void apply_detection_bloc_solid_Y_aux(dynamic_object_t* object, int bloc1, int bloc2)
{
    while((get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID
    || get_type(bloc1) == MAP_OBJECT_SEMI_SOLID || get_type(bloc2) == MAP_OBJECT_SEMI_SOLID)
    && object->ys > 0)
    {
        object->ys--;
        bloc1 = map_get((object->positionMap.x + 5) / MAP_PIXEL, (object->positionMap.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        bloc2 = map_get((object->positionMap.x + object->sprite->display_width - 5) / MAP_PIXEL,(object->positionMap.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
    }
    object->state = OBJECT_STATE_GROUND;
}

void apply_detection_bloc_solid_Y(dynamic_object_t* object)
{
    if(object->ys > 0) // Vers le bas
    {
        int bloc1 = map_get((object->positionMap.x + 5) / MAP_PIXEL, (object->positionMap.y + object->ys + object->sprite->display_height) / MAP_PIXEL);
        int bloc2 = map_get((object->positionMap.x + object->sprite->display_width - 5) / MAP_PIXEL, (object->positionMap.y + object->ys + object->sprite->display_height) / MAP_PIXEL);

        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID)
        {
            apply_detection_bloc_solid_Y_aux(object, bloc1, bloc2);
        }
        else if(get_type(bloc1) == MAP_OBJECT_SEMI_SOLID || get_type(bloc2) == MAP_OBJECT_SEMI_SOLID)
        {
            int bloc3 = map_get((object->positionMap.x + 5) / MAP_PIXEL, (object->positionMap.y + object->sprite->display_height - 5) / MAP_PIXEL);
            int bloc4 = map_get((object->positionMap.x + object->sprite->display_width - 5) / MAP_PIXEL, (object->positionMap.y + object->sprite->display_height - 5) / MAP_PIXEL);

            if(get_type(bloc3) != MAP_OBJECT_SEMI_SOLID && get_type(bloc4) != MAP_OBJECT_SEMI_SOLID)
            {
                apply_detection_bloc_solid_Y_aux(object, bloc1, bloc2);
            }
        }
    }
    else if(object->ys < 0) // Vers le haut
    {
        int bloc1 = map_get((object->positionMap.x + 5) / MAP_PIXEL,
         (object->positionMap.y + object->ys/2) / MAP_PIXEL);
        int bloc2 = map_get((object->positionMap.x + object->sprite->display_width - 5) / MAP_PIXEL,
         (object->positionMap.y + object->ys/2) / MAP_PIXEL);

        if(get_type(bloc1) == MAP_OBJECT_SOLID || get_type(bloc2) == MAP_OBJECT_SOLID)
        {
            object->ys = 0;
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
    printf("positionMap => %d, %d\n", object->positionMap.x, object->positionMap.y);
    printf("positionWorld => %d, %d\n", positionScreenWorld.x, positionScreenWorld.y);
    printf("Delta (y) => %d\n\n", (object->positionMap.y - object->positionScreen.y));
    printf("Speed => %f, %f\n", object->xs, object->ys);
    printf("Bloc => %d\n\n", get_type(map_get((object->positionMap.x + 5) / MAP_PIXEL, (object->positionMap.y + object->sprite->display_height - 1) / MAP_PIXEL)));
}
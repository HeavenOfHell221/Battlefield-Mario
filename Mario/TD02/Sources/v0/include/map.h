#ifndef MAP_IS_DEF
#define MAP_IS_DEF

#include <SDL_image.h>
#include "constants.h"
#include "object.h"
#include <stdio.h>
#include <stdlib.h>

enum 
{
    MAP_OBJECT_SOLID,
    MAP_OBJECT_SEMI_SOLID,
    MAP_OBJECT_AIR,
    MAP_OBJECT_LIQUID,
    MAP_OBJECT_COLLECTIBLE,
    MAP_OBJECT_DESTRUCTIBLE,
    MAP_OBJECT_EXPLOSIVE,
    MAP_OBJECT_TRANSPARENT
};

enum
{
    OBJECT_AIR = 0,
    OBJECT_FLOOR = 1,
    OBJECT_HERB = 2,
    OBJECT_GROUND = 3,
    OBJECT_WALL = 4,
    OBJECT_FLOWER = 5,
    OBJECT_FLOWER2 = 6,
    OBJECT_GRASS = 7,
    OBJECT_COIN = 8
};

typedef struct map_object_type
{
    sprite_t *sprite;
    int objectType;
    int ID;
    int direction; // LEFT or RIGHT
    //list_head_t global_chain;
    int current_animation;
    int animation_status; // normal direction or reversed
    int animation;
}map_object_type_t;

void map_new(unsigned width, unsigned height);
void map_allocate(unsigned width, unsigned height);
void map_set(int map_object, int x, int y);
int map_get(int x, int y);
void map_object_add(char* path, int nb_sprites, int steps_nb, int horizontal_anim_nb, int vertical_anim_nb, int type, int animation);
int get_type(int object);
void create_default_map(unsigned width, unsigned height);

extern int** map;
extern int countID;
extern map_object_type_t map_objects[];
extern map_object_type_t map_objects_Cursor[];

extern point_t positionScreenWorld;

#endif
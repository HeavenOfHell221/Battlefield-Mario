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
    MAP_OBJECT_NUM
};

typedef struct map_object_type
{
    sprite_t sprite;
    int objectType;
    int ID;
}map_object_type_t;

typedef struct _static_obj {
    sprite_t *sprite;
    int objectType;
    int ID;
    point_t positionMap;
    int direction; // LEFT or RIGHT
    list_head_t global_chain;
} static_object_t;

void map_new(unsigned width, unsigned height);
void map_allocate(unsigned width, unsigned height);
void map_set(int map_object, int x, int y);
int map_get(int x, int y);
void map_object_add(char* path, int nb_sprites, int type);
int get_type(int object);

extern int** map;
extern int countID;
extern map_object_type_t objects[];

extern point_t positionScreenWorld;

#endif
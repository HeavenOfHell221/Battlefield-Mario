#include "map.h"
#include "animation.h"

int** map;
int countID = 0;
map_object_type_t objects[5];
point_t positionScreenWorld;

void map_new(unsigned width, unsigned height)
{
    map_allocate(width, height);

    objects[countID].objectType = MAP_OBJECT_AIR;
    // Air, ID = 0
    map_object_add("../images/floor.png", 1, MAP_OBJECT_SEMI_SOLID); // ID = 1
    map_object_add("../images/herb.png", 1, MAP_OBJECT_AIR); // ID = 2
    map_object_add("../images/ground.png", 1, MAP_OBJECT_SOLID); // ID = 3
    map_object_add("../images/wall.png", 1, MAP_OBJECT_SOLID); // ID = 4

    // Sol
    for(int x = 0; x < width; x++)
    {
        map_set(3, x, height - 1);
    }

    // Murs
    for(int y = 0; y < height; y++)
    {
        map_set(4, 0, y);
        map_set(4, width - 1, y);
    }

    map_set(4, 3, 14);
    map_set(4, 4, 15);
    map_set(4, 5, 14);
    map_set(1, 6, 13);
    map_set(4, 7, 13);
    map_set(4, 8, 12);
    map_set(1, 9, 11);
    map_set(1, 10, 11);

    map_set(4, 25, 14);
    map_set(4, 26, 15);
    map_set(4, 26, 14);
    map_set(1, 27, 13);
    map_set(4, 28, 13);
    map_set(4, 29, 12);

    map_set(4, 13, 13);
    map_set(4, 14, 12);
    map_set(4, 15, 11);
    map_set(4, 16, 10);
    map_set(4, 17, 9);
    map_set(4, 18, 8);
    map_set(4, 19, 7);
    map_set(4, 20, 6);
    map_set(4, 21, 5);
    map_set(4, 22, 4);
    map_set(4, 23, 4);
    map_set(4, 24, 3);
    map_set(4, 25, 3);

    positionScreenWorld.x = 0;
    positionScreenWorld.y = 0;
}

void map_allocate(unsigned width, unsigned height)
{
    map = (int**) calloc(width, sizeof(int*));

    for(int i = 0; i < width; i++)
    {
        map[i] = calloc(height, sizeof(int));
    }
}

void map_set(int map_object, int x, int y)
{
    map[x][y] = map_object;

    static_object_t* obj = (static_object_t*) calloc(1, sizeof(static_object_t));

    obj->sprite = &objects[map_object].sprite;
    obj->objectType = objects[map_object].objectType; 
    obj->ID = objects[map_object].ID;
    obj->positionMap.x = x * MAP_PIXEL;
    obj->positionMap.y = y * MAP_PIXEL;
    obj->direction = LEFT;
    obj->global_chain.next = NULL;
    obj->global_chain.prev = NULL;
    animation_static_object_add(obj);
}

int map_get(int x, int y)
{
    return map[x][y];
}

void map_object_add(char* path, int nb_sprites, int type)
{
    countID++;
    sprite_create(&objects[countID].sprite, path, LEFT, nb_sprites, 1, 1, 1, 0, 1);
    objects[countID].objectType = type;
    objects[countID].ID = countID;   
}

int get_type(int object)
{
    return objects[object].objectType;
}
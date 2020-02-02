#include "map.h"
#include "animation.h"

int** map;
int countID = 0;
map_object_type_t objects[5];

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

    map_set(4, 3, 12);
    map_set(4, 4, 13);
    map_set(4, 5, 12);
    map_set(1, 6, 11);
    map_set(4, 7, 11);
    map_set(4, 8, 10);
    map_set(1, 9, 9);
    map_set(1, 10, 9);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            printf("%d ", map_get(x, y));
        }
        printf("\n");
    }
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
    obj->positionScreen.x = x * MAP_PIXEL;
    obj->positionScreen.y = y * MAP_PIXEL;
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
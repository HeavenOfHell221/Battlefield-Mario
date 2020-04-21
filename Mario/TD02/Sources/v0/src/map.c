#include "map.h"
#include "animation.h"

int** map;
int countID = 0;
map_object_type_t map_objects[NUMBER_OF_BLOCK_TYPE];
map_object_type_t map_objects_Cursor[NUMBER_OF_BLOCK_TYPE];
point_t positionScreenWorld;

void map_new(unsigned width, unsigned height)
{
    map_allocate(width, height);

    map_objects[0].objectType = MAP_OBJECT_AIR;
    map_objects[0].ID = 0;

    // Air, ID = 0
    map_object_add("../images/floor.png", 1, 1, 1, 1, MAP_OBJECT_SEMI_SOLID, 0); // ID = 1
    map_object_add("../images/herb.png", 1, 1, 1, 1, MAP_OBJECT_AIR, 0); // ID = 2
    map_object_add("../images/ground.png", 1, 1, 1, 1, MAP_OBJECT_SOLID, 0); // ID = 3
    map_object_add("../images/wall.png", 1,  1, 1, 1, MAP_OBJECT_SOLID, 0); // ID = 4

    map_object_add("../images/flower.png", 1, 1, 1, 1, MAP_OBJECT_AIR, 0); // ID = 5
    map_object_add("../images/flower2.png", 1, 1, 1, 1, MAP_OBJECT_AIR, 0); // ID = 6
    map_object_add("../images/grass.png", 1, 1, 1, 1, MAP_OBJECT_SEMI_SOLID, 0); // ID = 7
    map_object_add("../images/coin.png", 21, 21, 16, 2, MAP_OBJECT_COLLECTIBLE, 1); // ID = 8

    positionScreenWorld.x = 0;
    positionScreenWorld.y = 0;

    create_default_map(width, height);
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
}

int map_get(int x, int y)
{
    return map[x][y];
}

void map_object_add(char* path, int nb_sprites, int steps_nb, int horizontal_anim_nb, int vertical_anim_nb, int type, int animation)
{
    countID++;
    map_objects[countID].sprite = (sprite_t*) calloc(1, sizeof(sprite_t));

    sprite_create(map_objects[countID].sprite, path, LEFT, nb_sprites, steps_nb, horizontal_anim_nb, vertical_anim_nb, false, 1);
    map_objects[countID].objectType = type;
    map_objects[countID].ID = countID;   
    map_objects[countID].animation = animation;
    map_objects[countID].direction = LEFT;
    //map_objects[countID].global_chain.next = NULL;
    //map_objects[countID].global_chain.prev = NULL;
    map_objects[countID].current_animation = 0;
    map_objects[countID].animation_status = 1;
}

int get_type(int object)
{
    if(object >= 0 && object < 10)
    {
        return map_objects[object].objectType;
    }
    return 0;
}


void create_default_map(unsigned width, unsigned height)
{
     // Sol
    for(int x = 0; x < width; x++)
    {
        map_set(OBJECT_GROUND, x, height - 1);
    }

    // Murs
    for(int y = 0; y < height; y++)
    {
        map_set(OBJECT_WALL, 0, y);
        map_set(OBJECT_WALL, width - 1, y);
    }

    map_set(OBJECT_WALL, 8, 15);
    map_set(OBJECT_WALL, 3, 14);
    map_set(OBJECT_WALL, 4, 15);
    map_set(OBJECT_WALL, 5, 14);
    map_set(OBJECT_FLOOR, 6, 13);
    map_set(OBJECT_WALL, 8, 12);

    map_set(OBJECT_FLOOR, 10, 14);
    map_set(OBJECT_FLOOR, 11, 14);

    map_set(OBJECT_FLOOR, 10, 12);
    map_set(OBJECT_FLOOR, 11, 12);

    map_set(OBJECT_FLOOR, 10, 10);
    map_set(OBJECT_FLOOR, 11, 10);

    map_set(OBJECT_FLOOR, 10, 8);
    map_set(OBJECT_FLOOR, 11, 8);

    map_set(OBJECT_FLOOR, 10, 6);
    map_set(OBJECT_FLOOR, 11, 6);

    map_set(OBJECT_FLOOR, 10, 4);
    map_set(OBJECT_FLOOR, 11, 4);
    map_set(OBJECT_FLOOR, 12, 4);
    map_set(OBJECT_FLOOR, 13, 4);
    map_set(OBJECT_FLOOR, 14, 4);

    map_set(OBJECT_FLOOR, 10, 2);
    map_set(OBJECT_FLOOR, 11, 2);

    map_set(OBJECT_HERB, 11, 3);
    map_set(OBJECT_COIN, 12, 3);
    map_set(OBJECT_FLOWER, 13, 3);
    map_set(OBJECT_FLOWER2, 14, 3);

    map_set(OBJECT_WALL, 25, 14);
    map_set(OBJECT_WALL, 26, 15);
    map_set(OBJECT_WALL, 26, 14);
    map_set(OBJECT_FLOOR, 27, 13);
    map_set(OBJECT_WALL, 28, 13);
    map_set(OBJECT_WALL, 29, 12);

    map_set(OBJECT_WALL, 18, 13);
    map_set(OBJECT_WALL, 19, 12);
    map_set(OBJECT_WALL, 20, 11);
    map_set(OBJECT_WALL, 21, 10);
    map_set(OBJECT_WALL, 22, 9);
    map_set(OBJECT_WALL, 23, 8);
    map_set(OBJECT_WALL, 24, 7);
    map_set(OBJECT_WALL, 25, 6);
    map_set(OBJECT_WALL, 26, 5);
    map_set(OBJECT_WALL, 27, 5);

    map_set(OBJECT_COIN, 26, 4);
    map_set(OBJECT_COIN, 27, 4);
}
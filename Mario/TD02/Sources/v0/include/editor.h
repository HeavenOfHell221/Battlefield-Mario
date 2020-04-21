#ifndef EDITOR_IS_DEF
#define EDITOR_IS_DEF

#include "object.h"
#include "action.h"
#include "map.h"

void animation_cursor_moves(int left, int right, int up, int down, int espace, int tab);
void createCursor(point_t position, int currentBlock);

typedef struct cursor{

point_t position;

/*
OBJECT_AIR = 0,
OBJECT_FLOOR = 1,
OBJECT_HERB = 2,
OBJECT_GROUND = 3,
OBJECT_WALL = 4,
OBJECT_FLOWER = 5,
OBJECT_FLOWER2 = 6,
OBJECT_GRASS = 7,
OBJECT_COIN = 8
*/
int currentBlock;
action_t move;
action_t placeBlock;
action_t switchBlock;
map_object_type_t cursorLight;
} cursor_t;

extern int GAMEMODE;
extern cursor_t editorCursor;

#endif
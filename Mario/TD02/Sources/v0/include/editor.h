#ifndef EDITOR_IS_DEF
#define EDITOR_IS_DEF

#include "object.h"
#include "action.h"
#include "map.h"

typedef struct cursor {
point_t position; // Position dans le monde
int currentBlock; // Le block courant
action_t move; 
action_t placeBlock;
action_t switchBlock;
map_object_type_t cursorLight;
point_t positionCamMario;
point_t positionCamCursor;
} cursor_t;


void positionTest();
void animation_cursor_moves(cursor_t* editorCursor, int left, int right, int up, int down, int espace, int tab);
void createCursor(point_t position, int currentBlock);
void modeEditor(cursor_t* editorCursor);
void modeInGame(cursor_t* editorCursor);


extern int GAMEMODE;
extern cursor_t editorCursor;

#endif
#include "editor.h"

int GAMEMODE;
cursor_t editorCursor;


void createCursor(point_t position, int currentBlock)
{
    editorCursor.position.x = position.x;
    editorCursor.position.y = position.y;
    editorCursor.currentBlock = currentBlock;

    editorCursor.move.cooldown = 125;
    editorCursor.switchBlock.cooldown = 125;
    editorCursor.placeBlock.cooldown = 0;
    editorCursor.placeBlock.currentState = 1;
    editorCursor.cursorLight.sprite = &cursor_sprite;
    editorCursor.cursorLight.direction = LEFT;
    editorCursor.cursorLight.animation = 0;
}

void animation_cursor_moves(int left, int right, int up, int down, int espace, int tab)
{ 
    if(espace)
    {
        if(editorCursor.placeBlock.currentState)
        {
            map_set(map_get(editorCursor.position.x, editorCursor.position.y) == editorCursor.currentBlock ? 
            OBJECT_AIR : editorCursor.currentBlock, editorCursor.position.x, editorCursor.position.y);
            editorCursor.placeBlock.currentState = 0;
        }
    }
    else
    {
        editorCursor.placeBlock.currentState = 1;
    }

    if(tab && isPossibleAction(&editorCursor.switchBlock))
    {
        editorCursor.currentBlock = (editorCursor.currentBlock + 1) % NUMBER_OF_BLOCK_TYPE;

        if(editorCursor.currentBlock == 0) 
            editorCursor.currentBlock++;
    }


    if(left && isPossibleAction(&editorCursor.move))
    {
        editorCursor.position.x--;
        positionTest();
    }

    if(right && isPossibleAction(&editorCursor.move))
    {
        editorCursor.position.x++;
        positionTest();
    }

    if(up && isPossibleAction(&editorCursor.move))
    {
        editorCursor.position.y--;
        positionTest();
    }

    if(down && isPossibleAction(&editorCursor.move))
    {
        editorCursor.position.y++;
        positionTest();
    }

} 

void positionTest()
{
    editorCursor.position.x = editorCursor.position.x < 0 ? 0 
    : editorCursor.position.x > MAP_SIZE_X ? MAP_SIZE_X 
    : editorCursor.position.x;

    editorCursor.position.y = editorCursor.position.y < 0 ? 0 
    : editorCursor.position.y > MAP_SIZE_Y ? MAP_SIZE_Y
    : editorCursor.position.y; 
}
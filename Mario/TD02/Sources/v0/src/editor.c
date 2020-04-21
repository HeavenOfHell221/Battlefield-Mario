#include "editor.h"

int GAMEMODE;
cursor_t editorCursor;


void createCursor()
{
    editorCursor.position.x = MAP_SIZE_X/2;
    editorCursor.position.y = MAP_SIZE_Y/2;
    editorCursor.currentBlock = OBJECT_WALL;

    editorCursor.positionCamCursor.x = positionScreenWorld.x;
    editorCursor.positionCamCursor.y = positionScreenWorld.y;

    editorCursor.move.cooldown = 100; // en ms
    editorCursor.switchBlock.cooldown = 125; // en ms
    editorCursor.placeBlock.cooldown = 0;
    editorCursor.placeBlock.currentState = 1;

    editorCursor.cursorLight.sprite = &cursor_sprite;
    editorCursor.cursorLight.direction = LEFT;
    editorCursor.cursorLight.animation = 0;
}

void modeEditor(cursor_t* editorCursor)
{
    if(GAMEMODE != GAMEMODE_EDITOR)
    {
        GAMEMODE = GAMEMODE_EDITOR; // On passe en mode editor
        
        // Save de la caméra de Mario
        point_t positionCamMario = {positionScreenWorld.x, positionScreenWorld.y}; 
        editorCursor->positionCamMario = positionCamMario;

        // Load de la caméra du Cursor
        positionScreenWorld = editorCursor->positionCamCursor;
    }
}

void modeInGame(cursor_t* editorCursor)
{
    if(GAMEMODE != GAMEMODE_INGAME)
    {
        GAMEMODE = GAMEMODE_INGAME; // On passe en play

        // Save de la caméra du Cursor
        point_t positionCamCursor = {positionScreenWorld.x, positionScreenWorld.y}; 
        editorCursor->positionCamCursor = positionCamCursor;

        // Load de la caméra de Mario
        positionScreenWorld = editorCursor->positionCamMario;
    }
}

void animation_cursor_moves(cursor_t* editorCursor, int left, int right, int up, int down, int espace, int tab)
{ 
    // Event avec la touche Espace
    if(espace)
    {
        // Si on n'a pas encore posé de bloc lorsqu'on appui sur Espace
        if(editorCursor->placeBlock.currentState)
        {
            // On change le bloc
            // On met de l'air si le curseur est le même bloc que celui de la map
            // Sinon on remplace la map par le bloc du curseur
            map_set(map_get(editorCursor->position.x, editorCursor->position.y) == editorCursor->currentBlock ? 
            OBJECT_AIR : editorCursor->currentBlock, editorCursor->position.x, editorCursor->position.y);
            editorCursor->placeBlock.currentState = 0; // Interdiction de reposer un bloc tant lâche pas Espace
        }
    }
    else
    {
        // Quand on lâche Espace, on réautorise ) poser un bloc
        editorCursor->placeBlock.currentState = 1;
    }

    // Event avec la touche Tab
    if(tab && isPossibleAction(&editorCursor->switchBlock))
    {
        editorCursor->currentBlock = (editorCursor->currentBlock + 1) % NUMBER_OF_BLOCK_TYPE;

        if(editorCursor->currentBlock == 0) 
        {
            editorCursor->currentBlock++;
        }
    }

    // Event avec la touche Left
    if(left && isPossibleAction(&editorCursor->move))
    {
        editorCursor->position.x--;
        positionTest(editorCursor);
        if((positionScreenWorld.x > 0) && (abs(editorCursor->position.x * MAP_PIXEL - positionScreenWorld.x) < 0.2 * WIN_WIDTH))
        {
            positionScreenWorld.x -= MAP_PIXEL;       
        }
    }

    // Event avec la touche Right
    if(right && isPossibleAction(&editorCursor->move))
    {
        editorCursor->position.x++;
        positionTest(editorCursor);

        if((positionScreenWorld.x < MAP_SIZE_X * MAP_PIXEL - WIN_WIDTH)  && (abs(editorCursor->position.x * MAP_PIXEL - positionScreenWorld.x) > 0.8 * WIN_WIDTH))
        {
            positionScreenWorld.x += MAP_PIXEL; 
            
        }
    }

    // Event avec la touche Up
    if(up && isPossibleAction(&editorCursor->move))
    {
        editorCursor->position.y--;
        positionTest(editorCursor);

        if((positionScreenWorld.y > 0) && (abs(editorCursor->position.y * MAP_PIXEL - positionScreenWorld.y) < 0.2 * WIN_HEIGHT))
        {
            positionScreenWorld.y -= MAP_PIXEL;       
        }
    }

    // Event avec le touche Down
    if(down && isPossibleAction(&editorCursor->move))
    {
        editorCursor->position.y++;
        positionTest(editorCursor);

        if((positionScreenWorld.y < MAP_SIZE_Y * MAP_PIXEL - WIN_HEIGHT) && (abs(editorCursor->position.y * MAP_PIXEL - positionScreenWorld.y) > 0.8 * WIN_HEIGHT))
        {
            positionScreenWorld.y += MAP_PIXEL;   
        }
    }
} 

void positionTest(cursor_t* editorCursor)
{
    editorCursor->position.x = editorCursor->position.x < 0 ? 0 
    : editorCursor->position.x > MAP_SIZE_X-1 ? MAP_SIZE_X-1 
    : editorCursor->position.x;

    editorCursor->position.y = editorCursor->position.y < 0 ? 0 
    : editorCursor->position.y > MAP_SIZE_Y-1 ? MAP_SIZE_Y-1
    : editorCursor->position.y; 
}
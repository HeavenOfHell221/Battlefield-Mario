#include "action.h"

void actionTab_init(action_t* actions)
{
    for(int i = 0; i < MAX_ACTION; i++)
    {
        setActionCooldown(&actions[i], 0);
        actions[i].lastTimeActionWasPerformed = 0;
        actions[i].currentState = 0;
    }
}

void action_init(action_t* action)
{
    action->cooldown = 0;
    action->lastTimeActionWasPerformed = 0;
    action->currentState = 0;
}

void action_init_init(dynamic_object_t* object, int index, int cooldown)
{
    if(index < MAX_ACTION)
    {
        setActionCooldown(&object->actions[index], cooldown);
        object->actions[index].lastTimeActionWasPerformed = SDL_GetTicks();
        object->actions[index].currentState = 0;
    }
}

int isPossibleAction(action_t* action)
{
    if(action != NULL)
    {
        Uint32 currentTime = SDL_GetTicks();
        if((currentTime - action->lastTimeActionWasPerformed) >= action->cooldown)
        {
            action->lastTimeActionWasPerformed = currentTime;
            return true;
        }
    }
    return false;
}

void setActionCooldown(action_t* action, int cooldown)
{
    if(action != NULL)
    {
        if(cooldown >= 0)
            action->cooldown = cooldown;
        else
            action->cooldown = 0;
    }
}

void changeCurrentState(action_t* action)
{
    if(action->currentState == 0)
        action->currentState = 1;
    else
        action->currentState = 0;
}
#ifndef ACTION_IS_DEF
#define ACTION_IS_DEF

#include <stdint.h>
#include "SDL.h"
#include "object.h"


void actionTab_init(action_t* actions);
void action_init(action_t* action);
action_t* createNewAction(int cooldown);
int isPossibleAction(action_t* action);
void setActionCooldown(action_t* action, int cooldown);
void changeCurrentState(action_t* action);
void action_init_init(dynamic_object_t* object, int index, int cooldown);

#endif
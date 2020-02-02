#ifndef BIRD_IS_DEF
#define BIRD_IS_DEF

#include <stdint.h>
#include "object.h"
#include "action.h"
#include "timer.h"
#include "debug.h"
#include "error.h"
#include "animation.h"
#include "badbird.h"
#include "constants.h"

extern dynamic_object_t bird_obj;

void createBird();
void animation_bird_moves(dynamic_object_t* obj, int up, int down, int espace);
int animation_bird_onestep(dynamic_object_t* object);
void timer_bird(dynamic_object_t* object);
void keyboardOffCallback_Expired(dynamic_object_t* object);
Uint32 keyboardOffCallback(Uint32 delay, void* param);
void bird_animation(dynamic_object_t* object);

#endif
#ifndef MARIO_IS_DEF
#define MARIO_IS_DEF

#include "object.h"
#include "action.h"
#include "missile.h"
#include "map.h"

extern dynamic_object_t mario_object;

void createMario();
void animation_mario_moves(dynamic_object_t* object, int left, int right, int up, int espace);
int animation_mario_onestep(dynamic_object_t* object);

void apply_gravity(dynamic_object_t* object);
void apply_motion(dynamic_object_t* object);
void apply_animation(dynamic_object_t* object);
void apply_max_edge(dynamic_object_t* object);
void apply_max_edge_X(dynamic_object_t* object);
void apply_max_edge_Y(dynamic_object_t* object);
void apply_block_detection_y(dynamic_object_t* object, int bloc_type);
void apply_block_detection_x(dynamic_object_t* object, int bloc_type);
void apply_detection(dynamic_object_t* object);
void apply_detection_bloc_solid_Y(dynamic_object_t* object);
void apply_detection_bloc_solid_X(dynamic_object_t* object);
void printDebug(dynamic_object_t* object);
void apply_detection_bloc_solid_Y_aux(dynamic_object_t* object, int bloc1, int bloc2);

#endif
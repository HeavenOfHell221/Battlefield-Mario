#ifndef ANIMATION_IS_DEF
#define ANIMATION_IS_DEF

#include <SDL.h>
#include <stdbool.h>
#include "object.h"
#include "bird.h"
#include "missile.h"
#include "explosion.h"
#include "graphics.h"

void animation_init ();
void animation_one_step (int left, int right, int up, int down, int espace);
void animation_render_objects ();
void animation_mobile_object_add (dynamic_object_t *object);
void animation_mobile_object_del (dynamic_object_t *object);
void animation_clean ();

extern list_head_t all_objects;

void animation_clean_one(dynamic_object_t *object);

#endif
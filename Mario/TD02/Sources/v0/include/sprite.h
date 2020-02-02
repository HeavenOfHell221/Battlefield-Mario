#ifndef SPRITE_IS_DEF
#define SPRITE_IS_DEF

#include <SDL.h>
#include <stdbool.h>
#include "debug.h"
#include "constants.h"
#include "error.h"

typedef struct {
SDL_Texture *texture;
int native_width;
int native_height;
int display_width;
int display_height;
int size_factor;
int original_direction;
int offsetX;
int images_number;
int animation_steps_number;
int horizontal_animation_number;
int vertical_animation_number;
bool is_animation_reversed;
// ...
} sprite_t;

extern sprite_t background_sprite;
extern sprite_t tree_sprite_tab[3];
extern sprite_t mario_sprite;
extern sprite_t missile_sprite;
extern sprite_t explosion_sprite;
extern sprite_t ground_sprite;

extern SDL_Renderer* ren;

// Initialize sprite_t global variables for each sprite
void sprite_init (char *background_skin);

// Destroys
void sprite_clean (void);
void sprite_create(sprite_t *sprite, char *path, int original_direction, int images_number, int steps_nb, int horizontal_anim_nb, int vertical_anim_nb, bool reverse_animation, int size_factor);

#endif
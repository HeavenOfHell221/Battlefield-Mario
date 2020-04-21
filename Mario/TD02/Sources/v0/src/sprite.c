#include <SDL_image.h>
#include "sprite.h"

SDL_Texture *tree[3] = { NULL, NULL, NULL };
sprite_t background_sprite;
sprite_t tree_sprite_tab[3];
sprite_t mario_sprite;
sprite_t missile_sprite;
sprite_t explosion_sprite;
sprite_t ground_sprite;
sprite_t cursor_sprite;

void sprite_create(sprite_t *sprite, char *path, int original_direction, int images_number, int steps_nb, 
int horizontal_anim_nb, int vertical_anim_nb, bool reverse_animation, int size_factor)
{
    SDL_Texture* tex = IMG_LoadTexture (ren, path);
    if (tex == NULL)
        exit_with_error ("IMG_LoadTexture");
    else
        sprite->texture = tex;

    SDL_SetTextureBlendMode(sprite->texture, SDL_BLENDMODE_BLEND);//This sets the texture in blendmode
    int width, height;
    SDL_QueryTexture (sprite->texture, NULL, NULL, &width, &height);
    sprite->native_width = width;
    sprite->native_height = height;
    sprite->display_width = sprite->native_width  / horizontal_anim_nb;
    sprite->display_height = sprite->native_height / vertical_anim_nb;
    sprite->original_direction = original_direction;
    sprite->offsetX = 0;
    sprite->images_number = images_number;
    sprite->animation_steps_number = steps_nb;
    sprite->horizontal_animation_number = horizontal_anim_nb;
    sprite->vertical_animation_number = vertical_anim_nb;
    sprite->is_animation_reversed = reverse_animation;
    sprite->size_factor = size_factor;
}

void sprite_init (char *background_skin)
{
    char name[128];
    sprintf (name, "../images/%s-background.png", background_skin);

    sprite_create(&background_sprite, name, LEFT, 1, 1, 1, 1, false, 1);
    sprite_create(&mario_sprite, "../images/mario.png", RIGHT, 11, 11, 11, 1, true, 1);
    for (int i=0; i<3; i++)
    {
        sprintf (name, "../images/%s-%d.png", background_skin, i);
        sprite_create(&tree_sprite_tab[i], name, LEFT, 1, 1, 1, 1, false, 1);
    }
    sprite_create(&missile_sprite, "../images/missiled.png", RIGHT, 12, 12, 12, 1, false, 1);
    sprite_create(&explosion_sprite, "../images/explosion.png", RIGHT, 25, 24, 5, 5, false, 2);
    sprite_create(&ground_sprite, "../images/ground.png", RIGHT, 1, 1, 1, 1, false, 1);
    sprite_create(&cursor_sprite, "../images/cursor.png", LEFT, 1, 1, 1, 1, false, 1);
}

void sprite_clean()
{
    if(background_sprite.texture != NULL)
    {
        SDL_DestroyTexture (background_sprite.texture);
    }

	for (int i = 0; i < 3; i++)
    {
        sprite_t* ptr = &tree_sprite_tab[i];
        
        if(ptr != NULL)
        {
            if(ptr->texture != NULL)
            {
                SDL_DestroyTexture (tree_sprite_tab[i].texture);
            }
        }
    }

    if(mario_sprite.texture != NULL)
    {
        SDL_DestroyTexture (mario_sprite.texture);  
    }
   
    if(missile_sprite.texture != NULL)
    {
        SDL_DestroyTexture (missile_sprite.texture);
    }

    if(explosion_sprite.texture != NULL)
    {
        SDL_DestroyTexture (explosion_sprite.texture);
    }
	
}

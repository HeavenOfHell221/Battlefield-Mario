#include <SDL_image.h>
#include "graphics.h"

static SDL_Window *win = NULL;

void graphics_init (Uint32 render_flags, char *background_skin)
{
  // SDL initialisation
  if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
    exit_with_error ("SDL_Init");

  atexit (sprite_clean);
  atexit (animation_clean);
  atexit (graphics_clean);
  atexit (generator_clean);

  // Create main window
  win = SDL_CreateWindow ("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			  WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL)
    exit_with_error ("SDL_CreateWindow");

  // Initialize graphical accelerated renderer
  ren = SDL_CreateRenderer (win, -1, render_flags);
  if (ren == NULL)
    exit_with_error ("SDL_CreateRenderer");
}

static void graphics_render_background (sprite_t* background)
{
  SDL_Rect dst;

  dst.x = 0;
  dst.y = 0;
  dst.w = background->native_width;
  dst.h = WIN_HEIGHT;
  
  while(dst.x <= WIN_WIDTH){
    SDL_RenderCopy (ren, background->texture, NULL, &dst);
    dst.x += background->native_width;
  }
}

void graphics_render_object(dynamic_object_t* object)
{
  SDL_Rect src, dst;
  src.x = (object->current_animation % object->sprite->horizontal_animation_number) * object->sprite->display_width;
  if(object->sprite->vertical_animation_number == 1)
  {
    src.y =  0;
  }
  else
  {
    src.y = object->current_animation / object->sprite->vertical_animation_number * object->sprite->display_height;
  }
  src.w = object->sprite->display_width;
  src.h = object->sprite->display_height;
  
  dst.x = object->positionMap.x - positionScreenWorld.x;
  dst.y = object->positionMap.y - positionScreenWorld.y;
  dst.w = object->sprite->display_width * object->sprite->size_factor;
  dst.h = object->sprite->display_height * object->sprite->size_factor;

  SDL_RendererFlip Flip = SDL_FLIP_NONE;

  if (object->sprite->original_direction != object->direction)
  {
    Flip = SDL_FLIP_HORIZONTAL;
  }

  SDL_RenderCopyEx (ren, object->sprite->texture, &src, &dst, 0, NULL, Flip);
}

void graphics_render_object_static(static_object_t* currentObject)
{
  SDL_Rect src, dst;

  if(currentObject->animation == 1)
  {
    currentObject->current_animation = (currentObject->current_animation + currentObject->animation_status) % currentObject->sprite->images_number;

    src.x = (currentObject->current_animation % currentObject->sprite->horizontal_animation_number) * currentObject->sprite->display_width;
    
    if(currentObject->sprite->vertical_animation_number == 1)
    {
      src.y =  0;
    }
    else
    {
      src.y = currentObject->current_animation / currentObject->sprite->vertical_animation_number * currentObject->sprite->display_height;
    }

    src.w = currentObject->sprite->display_width;
    src.h = currentObject->sprite->display_height;

    dst.x = currentObject->positionMap.x - positionScreenWorld.x;
    dst.y = currentObject->positionMap.y - positionScreenWorld.y;
    dst.w = currentObject->sprite->display_width;
    dst.h = currentObject->sprite->display_height;

    SDL_RendererFlip Flip = SDL_FLIP_NONE;

    if (currentObject->sprite->original_direction != currentObject->direction)
    {
      Flip = SDL_FLIP_HORIZONTAL;
    }

    SDL_RenderCopyEx (ren, currentObject->sprite->texture, &src, &dst, 0, NULL, Flip);
  }
  else
  {
    dst.x = currentObject->positionMap.x - positionScreenWorld.x;
    dst.y = currentObject->positionMap.y - positionScreenWorld.y;
    dst.w = currentObject->sprite->display_width;
    dst.h = currentObject->sprite->display_height;

    SDL_RenderCopy (ren, currentObject->sprite->texture, NULL, &dst);
  }
}

void graphics_render_scrolling_trees (sprite_t* sprite, double factor)
{
  int scroll_speed = 0;
  
  if(mario_object.canMoveTrees == 1)
    scroll_speed = mario_object.xs * factor;  

  SDL_Rect dst;
  sprite->offsetX = (sprite->offsetX - scroll_speed) %  sprite->native_width;
  dst.x = sprite->offsetX;
  dst.y = 0;
  dst.w = sprite->native_width;
  dst.h = WIN_HEIGHT;

  while(dst.x <= WIN_WIDTH)
  {
    SDL_RenderCopy (ren, sprite->texture, NULL, &dst);
    dst.x += sprite->native_width;
  }

  while(dst.x > 0)
  {
    dst.x -= sprite->native_width;
    SDL_RenderCopy (ren, sprite->texture, NULL, &dst);
  }
}

void graphics_render (void)
{
  static Uint32 prev = 0;
  Uint32 begin, end, interm;

  begin = SDL_GetTicks ();
  
  // We clear the renderer's buffer
  SDL_RenderClear (ren);

  // We display the background clouds
  graphics_render_background (&background_sprite);

  graphics_render_scrolling_trees(&tree_sprite_tab[2], 0.3);
  graphics_render_scrolling_trees(&tree_sprite_tab[1], 0.6);
  graphics_render_scrolling_trees(&tree_sprite_tab[0], 1);

  animation_render_objects();

  interm = SDL_GetTicks ();
  
  // We update the visible screen. SDL uses a double buffering, so
  // previous modifications are not yet visible
  SDL_RenderPresent (ren);

  end =  SDL_GetTicks ();
  
  if (debug_enabled ('p')) {
    printf ("Animation: %2d, Rendering: %2d ms, VSync: %2d, Total: %2d ms)\r",
	    begin - prev,
	    interm - begin,
	    end - interm,
	    end - prev);
    fflush (stdout);
  }

  prev = end;
}

void graphics_clean (void)
{
  if(ren != NULL)
    SDL_DestroyRenderer (ren);

  if(win != NULL)
    SDL_DestroyWindow (win);

  IMG_Quit ();
  SDL_Quit ();
}

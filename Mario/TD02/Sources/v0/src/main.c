#include <stdio.h>
#include "SDL.h"
#include "SDL_image.h"
#include <string.h>

#include "graphics.h"
#include "error.h"
#include "debug.h"
#include "constants.h"
#include "animation.h"
#include "missile.h"
#include "generator.h"

#define DEFAULT_BACKGROUND_SKIN  "trees"

static char *progname;
static char *skin = NULL;
SDL_Renderer* ren;

typedef void (*func_t) (void*);
func_t p;

void usage (int val)
{
  fprintf (stderr, "Usage: %s [option]\n", progname);
  fprintf (stderr, "option can be:\n");
  fprintf (stderr, "\t-nvs\t| --no-vsync\t\t: disable vertical screen sync\n");
  fprintf (stderr, "\t-s\t| --skin <name>\t\t: use specific background skin\n");
  fprintf (stderr, "\t-d\t| --debug-flags <flags>\t: enable debug messages\n");
  fprintf (stderr, "\t-h\t| --help\t\t: display help\n");

  exit (val);
}

int main (int argc, char **argv)
{
  Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  char *debug_flags = NULL;

  progname = argv[0];

  // Filter args
  //
  argv++; argc--;
  while (argc > 0) {
    if (!strcmp (*argv, "--no-vsync") || !strcmp (*argv, "-nvs")) {      
      render_flags &= ~SDL_RENDERER_PRESENTVSYNC;
    } else if(!strcmp (*argv, "--help") || !strcmp (*argv, "-h")) {
      usage (0);
    } else if (!strcmp (*argv, "--debug-flags") || !strcmp (*argv, "-d")) {
      if (argc == 1) {
	fprintf (stderr, "Error: flag list missing\n");
	usage (1);
      }
      argc--; argv++;
      debug_flags = *argv;
    } else if (!strcmp (*argv, "--skin") || !strcmp (*argv, "-s")) {
      if (argc == 1) {
	fprintf (stderr, "Error: skin name missing\n");
	usage (1);
      }
      argc--; argv++;
      skin = *argv;
    } else
      break;
    argc--; argv++;
  }

  if (argc > 0)
    usage (1);

  debug_init (debug_flags);
  graphics_init (render_flags, (skin ? skin : DEFAULT_BACKGROUND_SKIN));

  const Uint8 *keystates = SDL_GetKeyboardState (NULL);
  
  sprite_init((skin ? skin : DEFAULT_BACKGROUND_SKIN));
  object_init();
  animation_init();
  map_new(MAP_SIZE_X, MAP_SIZE_Y);

  for (int quit = 0; !quit;) { //Gab : C'est un while si tu veut, si ça t'aide
    SDL_Event evt;

    // We look for keyboard/mouse events (in a non-blocking way)
    while (SDL_PollEvent (&evt)) {

      switch (evt.type) {

      case SDL_QUIT:
    	// If user closes the window
      quit = 1;
      break;

      case SDL_USEREVENT:
        p = evt.user.data1;
        p(evt.user.data2);
      break;

      case SDL_KEYDOWN:
    	  // if user presses a key
	      switch (evt.key.keysym.sym) {
	  
	      case SDLK_ESCAPE:
        // ESC : we quit!
        quit = 1;
        break;
	  
	      default: ;
	  
	      }
	    break ;

      default: ;
      }
    }

    // Check if up/down keys are currently pressed
    int up = keystates[SDL_SCANCODE_UP];
    int down = keystates[SDL_SCANCODE_DOWN];
    int left = keystates[SDL_SCANCODE_LEFT];
    int right = keystates[SDL_SCANCODE_RIGHT];
    int espace = keystates[SDL_SCANCODE_SPACE];
  
    animation_one_step(left, right, up, down, espace);
    graphics_render();
  }

  return 0;
}

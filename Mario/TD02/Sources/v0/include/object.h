#ifndef OBJECT_IS_DEF
#define OBJECT_IS_DEF

#include <SDL.h>
#include <stdint.h>
#include "sprite.h"
#include "constants.h"
#include "list.h"
#include "debug.h"

enum {
    OBJECT_TYPE_MARIO,
    OBJECT_TYPE_MISSILE,
    OBJECT_TYPE_EXPLOSION,
    OBJECT_TYPE_TEXT,
    __OBJECT_TYPE_NUM
};

enum {
    OBJECT_STATE_NORMAL,
    OBJECT_STATE_GROUND,
    OBJECT_STATE_IN_AIR,
    OBJECT_STATE_DESTROYED,
    OBJECT_STATE_DEAD
};

typedef SDL_TimerID timer_id_t;
typedef Uint32 (* timer_callback_func_t)(Uint32 delay, void* param);

typedef struct timer {
    timer_id_t id;
    timer_callback_func_t callback;
}myTimer_t;

typedef struct point {
    int x;
    int y;
} point_t;

typedef struct action {
    int cooldown; // ms
    Uint32 lastTimeActionWasPerformed; // ms
    int currentState;
} action_t;

typedef struct _dyn_obj {
    sprite_t *sprite;
    int type; // can be OBJECT_TYPE_BIRD, ...
    int state; // can be OBJECT_STATE_NORMAL, ...
    point_t positionScreen;
    point_t positionMap;
    float xs, ys; // speed
    int direction; // LEFT or RIGHT
    int current_animation;
    int animation_status; // normal direction or reversed
    list_head_t global_chain;
    action_t nextAnimationStep;
    action_t actions[MAX_ACTION];
    myTimer_t timer;
    int canMoveTrees;
    int speed;
} dynamic_object_t;


typedef int (* animate_func_t)(dynamic_object_t *object);
typedef void (* timer_func_t)(dynamic_object_t* object);

typedef struct {
    animate_func_t animate_func;
    timer_func_t timer_func;
} object_type_t;

extern object_type_t object_class[];

// Initialize the object_class array
void object_init ();

// Initialize fields of object obj
void object_object_init (dynamic_object_t *obj, sprite_t *sp, int type, int state, int x, int y, int speed, int direction, int animation_status);


#define for_all_objects_dyn(var) \
	list_for_each_entry_safe(dynamic_object_t, var, &all_objects_dyn, global_chain)

#define for_all_objects_static(var) \
	list_for_each_entry_safe(static_object_t, var, &all_objects_static, global_chain)

#endif
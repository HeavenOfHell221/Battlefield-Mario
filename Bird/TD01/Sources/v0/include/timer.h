#ifndef TIMER_IS_DEF
#define TIMER_IS_DEF

#include <stdint.h>
#include "object.h"

void timer_init (myTimer_t* timer);
timer_id_t timer_set (Uint32 delay, timer_callback_func_t callback, void* param);
int timer_cancel (timer_id_t timer_id);
void timer_init_init(dynamic_object_t* object, timer_callback_func_t callback);
void timer_callback_expired(void* callback, void* param);

#endif
#include "timer.h"

void timer_init (myTimer_t* timer)
{
   timer->id = 0;
   timer->callback = NULL;
}

void timer_init_init(dynamic_object_t* object, timer_callback_func_t callback)
{
   if(callback != NULL)
   {
      object->timer.id = 0;
      object->timer.callback = callback;
   }
}

timer_id_t timer_set (Uint32 delay, timer_callback_func_t callback, void* param)
{   
   return SDL_AddTimer(delay, callback, param);
}

int timer_cancel (timer_id_t timer_id)
{
   return SDL_RemoveTimer(timer_id);
}

void timer_callback_expired(void* callback, void* param)
{
  SDL_Event event;
  SDL_UserEvent userevent;
  userevent.type = SDL_USEREVENT;
  userevent.code = 0;
  userevent.data1 = callback;
  userevent.data2 = param;
  event.type = SDL_USEREVENT;
  event.user = userevent;
  SDL_PushEvent(&event);
}
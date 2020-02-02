#include "bird.h"

dynamic_object_t bird_obj;

enum {
    shotMissile = 0,
    blinkTexture = 1
};

void createBird()
{
  object_object_init(&bird_obj, &bird_sprite, OBJECT_TYPE_BIRD, OBJECT_STATE_IN_AIR, WIN_WIDTH/8 - bird_sprite.display_width/2, WIN_HEIGHT/2, 4, 0, RIGHT, NORMAL_DIRECTION);
  
  action_init_init(&bird_obj, shotMissile, SHOT_MISSILE_DELAY);
  action_init_init(&bird_obj, blinkTexture, 250);
  
  timer_init_init(&bird_obj, keyboardOffCallback);
}

void animation_bird_moves(dynamic_object_t* object, int up, int down, int espace)
{
  if (up && object->state != OBJECT_STATE_DEAD)
  {
    if (object->position.y <= 0)
    {
      object->ys = 0;
    }
    else
    {
      if (object->ys > -MAX_ANTIGRAVITY)
        object->ys -= UP_IMPULSE;
    }
    setActionCooldown(&object->nextAnimationStep, 0);
  }
  else
    setActionCooldown(&object->nextAnimationStep, TIME_ANIMATION_BIRD_IN_AIR);

  if(espace && isPossibleAction(&object->actions[shotMissile]))
  {
      if(object->state != OBJECT_STATE_DEAD)
      {
        animation_missile_add(object);
      }   
  }
}

int animation_bird_onestep(dynamic_object_t* object)
{
  // Gravité
  if (object->ys < MAX_GRAVITY)
    object->ys += GRAVITY;
    
  // Update deplacement
  object->position.y += object->ys;

  // Detection trop haut
  if(object->position.y <= 0 && object->state != OBJECT_STATE_DEAD)
  {
    object->ys = 0;
  }    

  // Detection trop bas
  if(object->position.y > WIN_HEIGHT - object->sprite->display_height)
  {
    object->position.y = WIN_HEIGHT - object->sprite->display_height;
    if(object->state != OBJECT_STATE_DEAD)
      object->state = OBJECT_STATE_NORMAL;
    object->xs = 2;
  }
  else if(object->position.y > 0)
  {
    if(object->state != OBJECT_STATE_DEAD)
      object->state = OBJECT_STATE_IN_AIR;
    object->xs = 4;
  }

  if(object->state == OBJECT_STATE_DEAD)
  {
    if (isPossibleAction(&object->actions[blinkTexture]))
    {
      if(object->actions[blinkTexture].currentState == 0)
        SDL_SetTextureAlphaMod(object->sprite->texture, (Uint8) 255);
      else
        SDL_SetTextureAlphaMod(object->sprite->texture, (Uint8) 0);
      changeCurrentState(&object->actions[blinkTexture]);
    }
  }

  // Animation
  bird_animation(object);
      
  return object->state;
}

void bird_animation(dynamic_object_t* object)
{
  if (object->sprite->is_animation_reversed)
  {
    if (object->current_animation == 0)
      object->animation_status = NORMAL_DIRECTION;
    if (object->current_animation == object->sprite->animation_steps_number)
      object->animation_status = REVERSED_DIRECTION;
    if (isPossibleAction(&object->nextAnimationStep))
      object->current_animation = object->current_animation + object->animation_status;
  }
  else
  {
     if (isPossibleAction(&object->nextAnimationStep))
      object->current_animation = (object->current_animation + object->animation_status) % object->sprite->images_number;
  }
}

void timer_bird(dynamic_object_t* object)
{
  if(object->timer.callback != NULL)
  {
    object->state = OBJECT_STATE_DEAD;
    object->ys = 0;  
    object->timer.id = timer_set(TIME_BIRD_DEAD, object->timer.callback, object);
  }
}

Uint32 keyboardOffCallback(Uint32 delay, void* param)
{
  timer_callback_expired(keyboardOffCallback_Expired, param);
  return delay;
}

void keyboardOffCallback_Expired(dynamic_object_t* object)
{
  object->state = OBJECT_STATE_NORMAL;

  timer_cancel(object->timer.id);
  SDL_SetTextureAlphaMod(object->sprite->texture, (Uint8) 255);
}
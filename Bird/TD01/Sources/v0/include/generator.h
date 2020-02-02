#ifndef GENERATOR_IS_DEF
#define GENERATOR_IS_DEF

#include <math.h>
#include "timer.h"
#include "badbird.h"

void generator_init();
Uint32 spawnBadbirdCallback(Uint32 delay, void* param);
void generator_clean();
void spawnBadbirdCallback_Expired(dynamic_object_t* object);

#endif
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

myTimer_t generateBadbirdTimer;
time_t t;

void generator_init()
{
    timer_init(&generateBadbirdTimer);
    generateBadbirdTimer.id = timer_set(500, spawnBadbirdCallback, NULL);
    srand((unsigned) time(&t));
}

Uint32 spawnBadbirdCallback(Uint32 delay, void* param)
{    
    timer_callback_expired(spawnBadbirdCallback_Expired, param);
    delay = (rand()%1501 + 500); // 500 ms et 2000 ms
    return delay;
}

void spawnBadbirdCallback_Expired(dynamic_object_t* object)
{
    int y = rand() % WIN_HEIGHT;
    int pi2 = M_PI * 2;
    int offset = rand() % pi2; // 0 et 2*pi
    int speed = (rand() % 4) + 2; // 2 et 5
    int period = (rand() % 8) + 8; // 8 et 15

    animation_badbird_add (1600, y, 0.07, period, speed, offset);
}

void generator_clean()
{
    timer_cancel(generateBadbirdTimer.id);
}
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

myTimer_t generateBadbirdTimer;
time_t t;

void generator_init()
{
    srand((unsigned) time(&t));
}

void generator_clean()
{
    timer_cancel(generateBadbirdTimer.id);
}
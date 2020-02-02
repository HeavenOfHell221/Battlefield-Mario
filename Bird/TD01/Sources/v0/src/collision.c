#include "collision.h"

int testCollisionBetweenTwoObjects(dynamic_object_t* object_1, dynamic_object_t* object_2)
{
    if(object_1 == NULL || object_2 == NULL)
        return 0;
    
    int leftA = object_1->position.x;
    int leftB = object_2->position.x;

    int topA = object_1->position.y;
    int topB = object_2->position.y;

    int rightA = leftA + object_1->sprite->display_width;
    int rightB = leftB + object_2->sprite->display_height;

    int bottomA = topA + object_1->sprite->display_width;
    int bottomB = topB + object_2->sprite->display_height;

    if(bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB)
    {
        return 0;
    }
    return 1;
}
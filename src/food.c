#include <stdlib.h>

#include "game.h"
#include "food.h"

void food_spawn(game_t *game, food_t *food)
{
    food->x = (rand() / (RAND_MAX / (SNAKE_X_MAX - SNAKE_X_MIN))) + SNAKE_X_MIN;
    food->y = (rand() / (RAND_MAX / (SNAKE_Y_MAX - SNAKE_Y_MIN))) + SNAKE_Y_MIN;
}

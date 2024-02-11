#ifndef FOOD_H
#define FOOD_H

typedef struct
{
    unsigned short int x;
    unsigned short int y;
} food_t;

void food_spawn(game_t *game, food_t *food);

#endif // food.h

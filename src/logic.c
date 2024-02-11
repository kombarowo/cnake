#include <stdbool.h>
#include <stddef.h>

#include "../include/game.h"
#include "../include/food.h"
#include "../include/snake.h"

bool is_x_wall(unsigned short int y)
{
    return y == 0 || y == SCREEN_HEIGHT - 1;
}
bool is_y_wall(unsigned short int x)
{
    return x == 0 || x == SCREEN_WIDTH - 1;
}
bool is_corner(unsigned short int x, unsigned short int y)
{
    return (x == 0 && y == 0) ||
           (x == SCREEN_WIDTH - 1 && y == 0) ||
           (x == 0 && y == SCREEN_HEIGHT - 1) ||
           (x == SCREEN_WIDTH - 1 && y == SCREEN_HEIGHT - 1);
}

bool is_food(unsigned short int x, unsigned short int y, food_t *food)
{
    return x == food->x && y == food->y;
}

bool is_snake_tail(unsigned short int x, unsigned short int y, game_t *game, snake_t *head)
{
    for (int i = 1; i < game->snake_length; i++)
    {
        if (x == (head + i)->x && y == (head + i)->y)
        {
            return true;
        }
    }

    return false;
}
bool is_snake_head(unsigned short int x, unsigned short int y, game_t *game, snake_t *head, food_t *food)
{
    if (x == head->x && y == head->y)
    {
        if (is_food(x, y, food))
        {
            snake_add(game, head);

            /* TODO: prevent collision with snake */
            food_spawn(game, food);

            return true;
        }

        if (is_snake_tail(x, y, game, head))
        {
            game->state = GAME_STATE_LOSE;
        }

        if (game->snake_length == SNAKE_MAX_LENGTH)
        {
            game->state = GAME_STATE_WIN;
        }

        return true;
    }

    return false;
}

#include <stdbool.h>
#include <stddef.h>

#include "game.h"
#include "food.h"
#include "snake.h"

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
bool is_snake_head(unsigned short int x, unsigned short int y, snake_t *head)
{
    return x == head->x && y == head->y;
}
void update_game_state(game_t *game, snake_t *head, food_t *food)
{
    if (is_snake_tail(head->x, head->y, game, head))
    {
        game->state = GAME_STATE_LOSE;
    }

    if (is_food(head->x, head->y, food))
    {
        snake_add(game, head);

        do {
            food_spawn(game, food);
        } while (
            is_snake_tail(food->x, food->y, game, head) ||
            is_snake_head(food->x, food->y, head)
        );
    }

    if (game->snake_length == SNAKE_MAX_LENGTH)
    {
        game->state = GAME_STATE_WIN;
    }
}

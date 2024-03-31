#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "render.h"
#include "logic.h"

void render_game_run(game_t *game, snake_t *head, food_t *food)
{
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            char ch = TEXTURE_FLOOR;

            if (is_food(x, y, food))
            {
                ch = TEXTURE_FOOD;
            }

            if (is_snake_head(x, y, head))
            {
                ch = TEXTURE_SNAKE_HEAD;
            }

            if (is_snake_tail(x, y, game, head))
            {
                ch = TEXTURE_SNAKE_TAIL;
            }

            if (is_x_wall(y))
                ch = TEXTURE_X_WALL;
            if (is_y_wall(x))
                ch = TEXTURE_Y_WALL;
            if (is_corner(x, y))
                ch = TEXTURE_CORNER;

            printf("%c", ch);
        }

        printf("\n");
    }

    printf("Head X, Y: %i, %i\n", head->x, head->y);
    printf("Food X, Y: %i, %i\n", food->x, food->y);
    printf("Snake size: %i / %i\n", game->snake_length, SNAKE_MAX_LENGTH);

    update_game_state(game, head, food);
}

void render_game_lose(game_t *game, snake_t *head, food_t *food)
{
    system("clear");
    printf("You died.\n");
    exit(0);
}

void render_game_win(game_t *game, snake_t *head, food_t *food)
{
    system("clear");
    printf("You win!\n");
    exit(0);
}

void render_game(game_t *game, snake_t *head, food_t *food)
{
    puts("\033[0;0H");

    switch (game->state)
    {
    case GAME_STATE_RUN:
        render_game_run(game, head, food);
        break;
    case GAME_STATE_LOSE:
        render_game_lose(game, head, food);
        break;
    case GAME_STATE_WIN:
        render_game_win(game, head, food);
        break;
    }

    usleep(1000 * 1000 * 1 / GAME_SPEED);
}

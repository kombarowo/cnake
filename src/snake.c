#include "game.h"
#include "snake.h"

char snake_get_direction(game_t *game, snake_t *head)
{
    switch (head->direction)
    {
    case ARROW_RIGHT_CHAR:
        return game->last_hitted_char == ARROW_LEFT_CHAR ? ARROW_RIGHT_CHAR : game->last_hitted_char;
    case ARROW_LEFT_CHAR:
        return game->last_hitted_char == ARROW_RIGHT_CHAR ? ARROW_LEFT_CHAR : game->last_hitted_char;
    case ARROW_DOWN_CHAR:
        return game->last_hitted_char == ARROW_UP_CHAR ? ARROW_DOWN_CHAR : game->last_hitted_char;
    case ARROW_UP_CHAR:
        return game->last_hitted_char == ARROW_DOWN_CHAR ? ARROW_UP_CHAR : game->last_hitted_char;
    default:
        return head->direction;
    }
}

void snake_move_chunk(snake_t *ch)
{
    switch (ch->direction)
    {
    case ARROW_RIGHT_CHAR:
        ch->x == SNAKE_X_MAX ? ch->x = SNAKE_X_MIN : ch->x++;
        break;
    case ARROW_LEFT_CHAR:
        ch->x == SNAKE_X_MIN ? ch->x = SNAKE_X_MAX : ch->x--;
        break;
    case ARROW_DOWN_CHAR:
        ch->y == SNAKE_Y_MAX ? ch->y = SNAKE_Y_MIN : ch->y++;
        break;
    case ARROW_UP_CHAR:
        ch->y == SNAKE_Y_MIN ? ch->y = SNAKE_Y_MAX : ch->y--;
        break;
    }
}

void snake_spawn(game_t *game, snake_t *head)
{
    head->x = 1;
    head->y = 1;
    head->direction = ARROW_RIGHT_CHAR;

    game->snake_length = 1;
}
void snake_move(game_t *game, snake_t *head)
{
    head->direction = snake_get_direction(game, head);

    for (int i = 0; i < game->snake_length; i++)
    {
        snake_move_chunk(head + i);
    }

    for (int i = game->snake_length - 1; i > 0; i--)
    {
        (head + i)->direction = (head + i - 1)->direction;
    }
}
void snake_add(game_t *game, snake_t *head)
{
    (head + game->snake_length)->x = (head + game->snake_length - 1)->x;
    (head + game->snake_length)->y = (head + game->snake_length - 1)->y;

    game->snake_length++;
}

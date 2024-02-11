#ifndef SNAKE_H
#define SNAKE_H

typedef struct
{
    unsigned short int x;
    unsigned short int y;
    char direction;
} snake_t;

void snake_spawn(game_t *game, snake_t *snake);
void snake_move(game_t *game, snake_t *snake);
void snake_add(game_t *game, snake_t *snake);

#endif // snake.h

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#define SCREEN_WIDTH 30
#define SCREEN_HEIGHT 8
#define SCREEN_BORDERS (SCREEN_WIDTH * 2 + (SCREEN_HEIGHT * 2 - 4))

#define GAME_SPEED 5
#define GAME_STATE_RUN 0
#define GAME_STATE_WIN 1
#define GAME_STATE_LOSE 2

#define ARROW_UP_CHAR 65
#define ARROW_LEFT_CHAR 68
#define ARROW_DOWN_CHAR 66
#define ARROW_RIGHT_CHAR 67

#define TEXTURE_FLOOR ' '
#define TEXTURE_X_WALL '-'
#define TEXTURE_Y_WALL '|'
#define TEXTURE_CORNER '+'
#define TEXTURE_FOOD '*'
#define TEXTURE_SNAKE_HEAD 'X'
#define TEXTURE_SNAKE_TAIL 'O'

#define SNAKE_MAX_LENGTH (SCREEN_WIDTH * SCREEN_HEIGHT - SCREEN_BORDERS)

#define SNAKE_X_MAX (SCREEN_WIDTH - 2)
#define SNAKE_Y_MAX (SCREEN_HEIGHT - 2)
#define SNAKE_X_MIN 1
#define SNAKE_Y_MIN 1

typedef struct
{
    unsigned short int state;
    unsigned short int snake_length;
    char last_hitted_char;
    bool is_fruit_spawned;
} game_t;

#endif // game.h

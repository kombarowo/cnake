#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <termios.h>
#include <time.h>
#include <stdlib.h>

#include "game.h"
#include "snake.h"
#include "food.h"
#include "render.h"
#include "terminal.h"

game_t game = {
    .state = GAME_STATE_RUN,
    .snake_length = 0,
    .is_fruit_spawned = 0,
    .last_hitted_char = ARROW_RIGHT_CHAR,
};

snake_t snake[SNAKE_MAX_LENGTH];

food_t food;

int main()
{
    /* TODO: mb find a better place to do that ? */
    srand(time(0));

    system("clear");

    pthread_t id_listen_keypress;
    pthread_create(&id_listen_keypress, NULL, listen_keypress, (void *)&game);

    snake_spawn(&game, snake);
    food_spawn(&game, &food);

    while (1)
    {
        snake_move(&game, snake);

        render_game(&game, snake, &food);
    }

    return 0;
}

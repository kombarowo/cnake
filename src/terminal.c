#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <pthread.h>

#include "../include/game.h"
#include "../include/terminal.h"

// https://www.opennet.ru/docs/FAQ/programming/unix-programming.html | 3.2 How can I read single characters from the terminal?

struct termios t_settings;

void reset_keypress(void)
{
    tcsetattr(0, TCSANOW, &t_settings);
    return;
}
void set_keypress(void)
{
    struct termios new_settings;

    tcgetattr(0, &t_settings);

    new_settings = t_settings;

    /* Disable canonical mode, and set buffer size to 1 byte */
    new_settings.c_lflag &= (~(ICANON | ECHO));
    new_settings.c_cc[VTIME] = 0;
    new_settings.c_cc[VMIN] = 1;

    tcsetattr(0, TCSANOW, &new_settings);

    atexit(&reset_keypress);

    return;
}
void *listen_keypress(void *arg)
{
    set_keypress();

    while (((game_t *)arg)->state == GAME_STATE_RUN)
    {
        char ch = getchar();

        if (
            ch == ARROW_RIGHT_CHAR ||
            ch == ARROW_LEFT_CHAR ||
            ch == ARROW_DOWN_CHAR ||
            ch == ARROW_UP_CHAR)
        {
            ((game_t *)arg)->last_hitted_char = ch;
        }
    }

    pthread_exit(0);
}

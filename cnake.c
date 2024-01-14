#include <pthread.h> // Multithreading
#include <stdio.h>
#include <stdlib.h>  // for atexit()
#include <termios.h> // For changing terminal mode
#include <unistd.h>  // For changing terminal mode

#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 30
#define GAME_SPEED 0.5
#define SNAKE_SIZE 0

struct termios original; // A struct to save the original state of terminal
struct snake_char
{
    int x;
    int y;
    char direction;
};
char lastCharHitted = 'd'; // For thread communication

void disableRAWMode();
void enableRAWMode();
void *waitForKeyboardHit();

void move(struct snake_char *el)
{
    switch (el->direction)
    {
    case 'd':
        el->x++;
        break;
    case 'a':
        el->x--;
        break;
    case 's':
        el->y++;
        break;
    case 'w':
        el->y--;
        break;
    }
}

int main()
{
    pthread_t id_read;

    pthread_create(&id_read, NULL, waitForKeyboardHit, NULL);

    struct snake_char snake_head;

    snake_head.x = 10;
    snake_head.y = 0;
    snake_head.direction = 'd';

    /* TODO: implement malloc to dynamic length */
    struct snake_char snake_tail[10];

    /* TODO: implement initial snake state */
    snake_tail[0].x = 9;
    snake_tail[0].y = 0;
    snake_tail[0].direction = 'd';

    while (1)
    {
        usleep(1000 * 1000 * 1);

        system("clear");

        if (lastCharHitted == 27)
        {
            printf("Game over!\n");
            break;
        }

        snake_head.direction = lastCharHitted;

        /* Move head and tail */
        move(&snake_head);
        for (int i = 0; i < sizeof(snake_tail) / sizeof(snake_head); i++)
        {
            move(&snake_tail[i]);
        }
        /* Set direction for tail */
        for (int i = sizeof(snake_tail) / sizeof(snake_head) - 1; i > 0; i--)
        {
            snake_tail[i].direction = snake_tail[i - 1].direction;
        }
        snake_tail[0].direction = snake_head.direction;

        /* Draw */
        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                if (x == snake_head.x && y == snake_head.y)
                {
                    printf("X");
                    continue;
                }

                /* TODO: Calc count of tail by pointer ^ */
                if (x == snake_tail[0].x && y == snake_tail[0].y)
                {
                    printf("#");
                    continue;
                }

                if (x == snake_tail[1].x && y == snake_tail[1].y)
                {
                    printf("#");
                    continue;
                }

                if (x == snake_tail[2].x && y == snake_tail[2].y)
                {
                    printf("#");
                    continue;
                }

                if (x == snake_tail[3].x && y == snake_tail[3].y)
                {
                    printf("#");
                    continue;
                }

                printf(".");
            }

            printf("\n");
        }
    }

    return 0;
}

/// Reads keyboard input
void *waitForKeyboardHit()
{
    enableRAWMode(); // local function: Enable Raw Mode

    while ((lastCharHitted = getchar()) != 27)
        printf("%c", lastCharHitted);
    ; // ASCI code for ESC is 27

    printf("ESC Pressed!\n");

    pthread_exit(0);
}

/// This function enables RAW mode for terminal.
void enableRAWMode()
{
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw); // Save the state of the terminal to struct raw
                                   // STDIN_FILENO is from <stdlib.h>
                                   // tcgetattr() from <termios.h>
    tcgetattr(STDIN_FILENO, &original);
    atexit(&disableRAWMode); // Revert to canonical mode when exiting the program
                             // atext() from <stdlib.h>
    raw.c_lflag &=
        ~(ECHO | ICANON); // Turn off canonical mode
                          // Turn off ECHO mode so that keyboard is not
                          // printing to terminal
                          // ICANON and ECHO is bitflag. ~ is binary NOT operator

    tcsetattr(STDIN_FILENO, TCSAFLUSH,
              &raw); // Set the terminal to be in raw mode
                     // tcsetattr() from <termios.h>
}

void disableRAWMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH,
              &original); // Set terminal to original state
}

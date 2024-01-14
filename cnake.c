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

int main()
{
    // Start Multithreading
    pthread_t id_read;

    pthread_create(&id_read, NULL, waitForKeyboardHit, NULL);

    struct snake_char snake_head;

    snake_head.x = 2;
    snake_head.y = 0;
    snake_head.direction = 'd';

    struct snake_char snake_tail[10];

    snake_tail[0].x = 1;
    snake_tail[0].y = 0;
    snake_tail[0].direction = 'd';

    snake_tail[1].x = 0;
    snake_tail[1].y = 0;
    snake_tail[1].direction = 'd';

    while (1)
    {
        sleep(1);

        system("clear");

        if (lastCharHitted == 27)
        {
            printf("Game over!\n");
            break;
        }

        snake_head.direction = lastCharHitted;

        switch (snake_head.direction)
        {
        case 'd':
            snake_head.x++;
            break;
        case 'a':
            snake_head.x--;
            break;
        case 's':
            snake_head.y++;
            break;
        case 'w':
            snake_head.y--;
            break;
        }
        switch (snake_tail[0].direction)
        {
        case 'd':
            snake_tail[0].x++;
            break;
        case 'a':
            snake_tail[0].x--;
            break;
        case 's':
            snake_tail[0].y++;
            break;
        case 'w':
            snake_tail[0].y--;
            break;
        }

        switch (snake_tail[1].direction)
        {
        case 'd':
            snake_tail[1].x++;
            break;
        case 'a':
            snake_tail[1].x--;
            break;
        case 's':
            snake_tail[1].y++;
            break;
        case 'w':
            snake_tail[1].y--;
            break;
        }

        snake_tail[1].direction = snake_tail[0].direction;
        snake_tail[0].direction = snake_head.direction;

        for (int y = 0; y < SCREEN_HEIGHT; y++)
        {
            for (int x = 0; x < SCREEN_WIDTH; x++)
            {
                if (x == snake_head.x && y == snake_head.y)
                {
                    // printf("%c", lastCharHitted);
                    printf("X");
                    continue;
                }

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

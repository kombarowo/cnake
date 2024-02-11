
#!/bin/bash

clear; gcc -Wall -Werror src/main.c src/snake.c src/food.c src/terminal.c src/logic.c src/render.c -o build/main

#!/bin/bash

gcc -Wall -Werror -I ./include \
src/main.c \
src/snake.c \
src/food.c \
src/terminal.c \
src/logic.c \
src/render.c \
-o build/main

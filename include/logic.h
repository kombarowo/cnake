#ifndef LOGIC_H
#define LOGIC_H

bool is_x_wall(unsigned short int y);
bool is_y_wall(unsigned short int x);
bool is_corner(unsigned short int x, unsigned short int y);

bool is_food(unsigned short int x, unsigned short int y, food_t *food);

bool is_snake_tail(unsigned short int x, unsigned short int y, game_t *game, snake_t *head);
bool is_snake_head(unsigned short int x, unsigned short int y, snake_t *head);

void update_game_state(game_t *game, snake_t *head, food_t *food);

#endif // logic.h

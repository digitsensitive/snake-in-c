#pragma once

#include "entity.h"

typedef struct Snake Snake;
struct Snake {
    Entity base;
    Position dir;
};

Snake* create_snake(int x, int y);

void update_snake(Snake* self);
void render_snake(Snake* self);

void set_snake_direction(Snake* snake, int x, int y);
void move_snake(Snake* snake);
void grow_snake(Snake* snake, int rate);

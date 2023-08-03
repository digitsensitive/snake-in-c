
#include "snake.h"

#include <ncurses.h>
#include <stdlib.h>

void update_snake(Snake* self) {
    Snake* snake = (Snake*)self;
    move_snake(snake);
}

void render_snake(Snake* self) {
    Snake* snake = (Snake*)self;
    mvaddch(snake->base.pos.y, snake->base.pos.x, snake->base.display_char);
}

Snake* create_snake(int x, int y) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));
    snake->base.display_char = 'X';
    snake->base.pos.x = x;
    snake->base.pos.y = y;

    set_snake_direction(snake, 1, 0);
    return snake;
}

void set_snake_direction(Snake* snake, int x, int y) {
    snake->dir.x = x;
    snake->dir.y = y;
}

void move_snake(Snake* snake) {
    // clear current char cell
    mvaddch(snake->base.pos.y, snake->base.pos.x, ' ');

    snake->base.pos.x += snake->dir.x;
    snake->base.pos.y += snake->dir.y;
}
#include "apple.h"

#include <ncurses.h>
#include <stdlib.h>

#include "../constants.h"

Apple* create_apple(int x, int y) {
    Apple* apple = (Apple*)malloc(sizeof(Apple));
    apple->base.display_char = 'O';
    apple->base.color = 2;
    apple->pos.x = x;
    apple->pos.y = y;

    return apple;
}

void update_apple(Apple* self) {}

void render_apple(Apple* self) {
    Apple* apple = (Apple*)self;
    attron(COLOR_PAIR(self->base.color));
    mvaddch(apple->pos.y, apple->pos.x, apple->base.display_char);
    attroff(COLOR_PAIR(self->base.color));
}

void reset_apple_position(Apple* self) {
    self->pos.x = get_random_int(1, GAME_WIDTH - 1);
    self->pos.y = get_random_int(1, GAME_HEIGHT - 1);
}
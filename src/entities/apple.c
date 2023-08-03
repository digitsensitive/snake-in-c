#include "apple.h"

#include <ncurses.h>
#include <stdlib.h>

#include "../constants.h"

Apple* create_apple(int x, int y) {
    Apple* apple = (Apple*)malloc(sizeof(Apple));
    apple->base.display_char = 'O';
    apple->base.pos.x = x;
    apple->base.pos.y = y;

    return apple;
}

void update_apple(Apple* self) {}

void render_apple(Apple* self) {
    Apple* apple = (Apple*)self;
    mvaddch(apple->base.pos.y, apple->base.pos.x, apple->base.display_char);
}

void reset_apple_position(Apple* self) {
    self->base.pos.x = get_random_int(1, GAME_WIDTH - 1);
    self->base.pos.y = get_random_int(1, GAME_HEIGHT - 1);
}
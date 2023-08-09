#include "apple.h"

#include <ncurses.h>
#include <stdlib.h>

#include "../ncurses/ncurses_utils.h"
#include "../ncurses/ncurses_window.h"
#include "../utils.h"

Apple* create_apple(char ch, int x, int y) {
    Apple* apple = (Apple*)malloc(sizeof(Apple));
    apple->base.display_char = ch;
    apple->base.color = ANSI_COLOR_GREEN;
    apple->base.update = (EntityUpdateFunc)update_apple;
    apple->base.render = (EntityRenderFunc)render_apple;
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
    self->pos.x = get_random_int(1, WINDOW_WIDTH - 2);
    self->pos.y = get_random_int(1, WINDOW_HEIGHT - 2);
}
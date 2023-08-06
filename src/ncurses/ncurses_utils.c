#include "ncurses_utils.h"

#include <ncurses.h>

// draw character at location x and y with specific color
void draw_char(const char ch, const int x, const int y, const int color) {
    attron(COLOR_PAIR(color));
    mvaddch(y, x, ch);
    attroff(COLOR_PAIR(color));
}
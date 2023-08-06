#include "ncurses_utils.h"

#include <ncurses.h>

/**
 * Activate colors for the terminal
 */
int init_colors() {
    // check first if terminal supports colours
    if (!has_colors()) {
        printf("ERROR: Terminal does not support Color.\n");
        return 0;
    }

    // init use of colours on terminal
    start_color();

    // define color pairs
    init_pair(ANSI_COLOR_BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(ANSI_COLOR_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(ANSI_COLOR_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(ANSI_COLOR_CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(ANSI_COLOR_RED, COLOR_RED, COLOR_RED);
    init_pair(ANSI_COLOR_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(ANSI_COLOR_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(ANSI_COLOR_WHITE, COLOR_WHITE, COLOR_WHITE);

    return 1;
}

/**
 * Draw a character at location (x,y) with a specified color
 */
void draw_char(const char ch, const int x, const int y, enum ANSIColor color) {
    attron(COLOR_PAIR(color));
    mvaddch(y, x, ch);
    attroff(COLOR_PAIR(color));
}
#include "ncurses_api.h"

const int WINDOW_WIDTH = 70;
const int WINDOW_HEIGHT = 25;

WINDOW* main_window;

int init_ncurses() {
    if ((main_window = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses window.\n");
        return 0;
    }

    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(main_window, true);

    // disable input blocking (f.e. for getch() and wgetch())
    nodelay(main_window, true);

    // set the cursor mode to "Invisible"
    curs_set(0);

    // init colors for the terminal
    if (!init_colors()) {
        endwin();
        return 0;
    }

    // resize the game field
    resize_term(WINDOW_HEIGHT, WINDOW_WIDTH);

    // draw a box around the screen
    box(main_window, 0, 0);

    // resize the window to fit text at the bottom
    resize_term(WINDOW_HEIGHT + 1, WINDOW_WIDTH);

    return 1;
}

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

void draw_text(const char* text, const int x, const int y) {
    mvprintw(y, x, text);
}
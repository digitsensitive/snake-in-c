#include "ncurses_window.h"

const int WINDOW_WIDTH = 70;
const int WINDOW_HEIGHT = 25;

WINDOW* main_window;

int init_ncurses_window() {
    if ((main_window = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses window.\n");
        return 0;
    }

    return 1;
}
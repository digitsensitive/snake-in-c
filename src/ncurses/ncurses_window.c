#include "ncurses_window.h"

WINDOW* main_window;

int init_ncurses_window() {
    if ((main_window = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses window.\n");
        return 0;
    }

    return 1;
}
#pragma once

#include <ncurses.h>

extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;
extern WINDOW* main_window;

int init_ncurses_window();
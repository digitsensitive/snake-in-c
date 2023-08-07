#pragma once

enum ANSIColor {
    ANSI_COLOR_BLACK = 1,
    ANSI_COLOR_BLUE,
    ANSI_COLOR_GREEN,
    ANSI_COLOR_CYAN,
    ANSI_COLOR_RED,
    ANSI_COLOR_MAGENTA,
    ANSI_COLOR_YELLOW,
    ANSI_COLOR_WHITE,
};

int init_colors();
void draw_char(const char ch, const int x, const int y, enum ANSIColor color);
void draw_text(const char *text, const int x, const int y);
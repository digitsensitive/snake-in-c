#include "clock.h"

#include <ncurses.h>
#include <time.h>

clock_t current_time = 0;
clock_t previous_time = 0;
float delta_time = 0.0f;

// Calculate time elapsed since the last iteration
void calculate_time_elapsed() {
    current_time = clock();
    delta_time = (float)(current_time - previous_time) / CLOCKS_PER_SEC;
    previous_time = current_time;
}

// Delay to achieve the desired FPS
void delay_clock() { napms(FRAME_TIME_MS); }

const float get_delta_time() { return delta_time; }
#pragma once

#define FPS 10
#define FRAME_TIME_MS (1000 / FPS)

void calculate_time_elapsed();
void delay_clock();
const float get_delta_time();
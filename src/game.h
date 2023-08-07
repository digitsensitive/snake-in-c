#pragma once

#include "entities/apple.h"
#include "entities/snake.h"

int init();
void run();
void input();
void update(float deltaTime);
void render();
void render_gui();
void check_for_collisions();
void is_outside_boundary();
void shutdown();

#pragma once

#include "entity.h"

typedef struct {
    Entity base;
    int health_points;
} Apple;

Apple* create_apple(int x, int y);
void update_apple(Apple* self);
void render_apple(Apple* self);
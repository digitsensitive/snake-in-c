#pragma once

#include "entity.h"

typedef struct Snake Snake;
typedef struct BodyNode BodyNode;
typedef struct BodyNode {
    Position pos;
    BodyNode* next;
} BodyNode;

struct Snake {
    Entity base;
    BodyNode* body;
    Position dir;
    int is_growing;
};

Snake* create_snake(char ch, int x, int y);
BodyNode* create_body_part(Snake* self, int x, int y);

void update_snake(Snake* self);
void render_snake(Snake* self);

void set_snake_direction(Snake* snake, int x, int y);
void move_snake(Snake* self);
void is_growing(Snake* self);
int snake_hit_snake(Snake* self);
void free_snake(Snake* self);
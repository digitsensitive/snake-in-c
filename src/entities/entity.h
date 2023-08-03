#pragma once

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int id;
    char display_char;
    Position pos;
} Entity;

void init_entity();

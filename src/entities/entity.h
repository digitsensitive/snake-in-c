#pragma once

typedef struct {
    int x;
    int y;
} Position;

typedef void (*EntityUpdateFunc)(void *entity);
typedef void (*EntityRenderFunc)(void *entity);
typedef struct {
    int id;
    int color;
    char display_char;
    EntityUpdateFunc update;
    EntityRenderFunc render;
} Entity;

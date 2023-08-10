
#include "snake.h"

#include <stdio.h>
#include <stdlib.h>

#include "../ncurses_api.h"

void update_snake(Snake* self) {
    move_snake(self);
    snake_hit_snake(self);
}

void render_snake(Snake* self) {
    BodyNode* current = self->body;
    while (current != NULL) {
        draw_char(self->base.display_char, current->pos.x, current->pos.y,
                  self->base.color);
        current = current->next;
    }
}

BodyNode* create_body_part(Snake* self, int x, int y) {
    BodyNode* body = malloc(sizeof(BodyNode));

    if (body != NULL) {
        body->pos.x = x;
        body->pos.y = y;
        body->next = NULL;
    } else {
        printf("Memory allocation failed!\n");
    }

    return body;
}

Snake* create_snake(char ch, int x, int y) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));

    // init base properties
    snake->base.display_char = ch;
    snake->base.color = ANSI_COLOR_YELLOW;
    snake->base.update = (EntityUpdateFunc)update_snake;
    snake->base.render = (EntityRenderFunc)render_snake;
    snake->is_growing = 0;
    snake->is_dying = 0;
    snake->body = create_body_part(snake, x, y);

    set_snake_direction(snake, 1, 0);
    return snake;
}

void set_snake_direction(Snake* snake, int x, int y) {
    if (snake->dir.x != -x || snake->dir.y != -y) {
        snake->dir.x = x;
        snake->dir.y = y;
    }
}

void move_snake(Snake* self) {
    BodyNode* current = self->body;
    while (current != NULL) {
        // clear current char cell
        draw_char(' ', current->pos.x, current->pos.y, 0);
        current = current->next;
    }

    BodyNode* curr = self->body;
    int prevX, prevY, tempX, tempY;

    // Move the head
    prevX = curr->pos.x;
    prevY = curr->pos.y;
    curr->pos.x += self->dir.x;
    curr->pos.y += self->dir.y;

    // Move the rest of the segments
    while (curr->next != NULL) {
        curr = curr->next;
        tempX = curr->pos.x;
        tempY = curr->pos.y;
        curr->pos.x = prevX;
        curr->pos.y = prevY;
        prevX = tempX;
        prevY = tempY;
    }

    if (self->is_growing) {
        BodyNode* tail = self->body;
        while (tail->next != NULL) {
            tail = tail->next;
        }

        tail->next = malloc(sizeof(BodyNode));
        tail->next->pos.x = prevX;
        tail->next->pos.y = prevY;
        tail->next->next = NULL;
        self->is_growing = 0;
    }
}

void is_growing(Snake* self) { self->is_growing = 1; }

void free_snake(Snake* self) {
    BodyNode* current = self->body;
    while (current != NULL) {
        BodyNode* temp = current;
        current = current->next;
        free(temp);
    }
}

void is_outside_boundary(Snake* self, int w, int h) {
    int x = self->body->pos.x;
    int y = self->body->pos.y;

    if (x < 1 || x > (w - 2) || y < 1 || y > h - 2) {
        self->is_dying = 1;
    }
}

void snake_hit_snake(Snake* self) {
    BodyNode* head = self->body;
    BodyNode* current = head->next;

    while (current != NULL) {
        if (head->pos.x == current->pos.x && head->pos.y == current->pos.y) {
            self->is_dying = 1;
        }

        current = current->next;
    }
}

int is_snake_dying(Snake* self) { return self->is_dying; }
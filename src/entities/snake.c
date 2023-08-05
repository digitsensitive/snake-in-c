
#include "snake.h"

#include <ncurses.h>
#include <stdlib.h>

void update_snake(Snake* self) {
    Snake* snake = (Snake*)self;
    move_snake(snake);
}

void render_snake(Snake* self) {
    Snake* snake = (Snake*)self;

    BodyNode* current = self->body;
    while (current != NULL) {
        attron(COLOR_PAIR(self->base.color));
        mvaddch(current->pos.y, current->pos.x, snake->base.display_char);
        attroff(COLOR_PAIR(self->base.color));
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

Snake* create_snake(int x, int y) {
    Snake* snake = (Snake*)malloc(sizeof(Snake));

    // init base properties
    snake->base.display_char = 'X';
    snake->base.color = 1;
    snake->is_growing = 0;
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
        mvaddch(current->pos.y, current->pos.x, ' ');
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

int snake_hit_snake(Snake* self) {
    BodyNode* head = self->body;
    BodyNode* current = head->next;

    while (current != NULL) {
        if (head->pos.x == current->pos.x && head->pos.y == current->pos.y) {
            return 1;
        }
        current = current->next;
    }

    return 0;
}
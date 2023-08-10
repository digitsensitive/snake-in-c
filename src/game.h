#pragma once

typedef struct {
    unsigned int score;
    char score_string[30];
    int is_running;
} Game;

Game* init_game();
void run_game(Game* game);
void shutdown();

void input(Game* game);
void update(float deltaTime);
void render();
void render_gui(Game* game);

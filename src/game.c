#include "game.h"

#include <stdlib.h>
#include <time.h>

#include "clock.h"
#include "entities/apple.h"
#include "entities/snake.h"
#include "languages.h"
#include "ncurses_api.h"
#include "utils.h"

// Entities
#define MAX_ENTITIES 2
Entity *entities[MAX_ENTITIES];
Snake *snake;
Apple *apple;

Game *init_game() {
    if (!init_ncurses()) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return NULL;
    }

    // Seed the random number generator with the current time
    srand(time(NULL));

    Game *game = (Game *)malloc(sizeof(Game));

    if (game == NULL) {
        fprintf(stderr, "Error initializing game instance.\n");
        return NULL;
    }

    game->score = 0;
    game->is_running = 1;

    // set language
    set_language(EN);

    snake = create_snake('X', 10, 5);
    entities[0] = (Entity *)snake;
    apple = create_apple('O', 20, 10);
    entities[1] = (Entity *)apple;

    return game;
}

void run_game(Game *game) {
    if (!snake->is_dying) {
        input(game);

        // Calculate time elapsed since the last iteration
        calculate_time_elapsed();

        // Update the game state based on time elapsed
        update(get_delta_time());

        // check snake-apple-collision
        if (apple->pos.x == snake->body->pos.x &&
            apple->pos.y == snake->body->pos.y) {
            // collision between snake and apple occured
            // add one point to the score
            game->score += 1;

            // set new random position for the apple
            reset_apple_position(apple);

            // grow snake
            is_growing(snake);
        }

        // Check if snake is outside boundary
        is_outside_boundary(snake, WINDOW_WIDTH, WINDOW_HEIGHT);

        // Render Entities
        render();

        // render GUI
        render_gui(game);

        // Delay to achieve the desired FPS
        delay_clock();

        refresh();
    } else {
        game->is_running = 0;
    }
}

void input(Game *game) {
    int in_char = wgetch(main_window);

    switch (in_char) {
        case 'q':
            game->is_running = 0;
            break;
        case KEY_UP:
        case 'w':
            set_snake_direction(snake, 0, -1);
            break;
        case KEY_DOWN:
        case 's':
            set_snake_direction(snake, 0, 1);
            break;
        case KEY_LEFT:
        case 'a':
            set_snake_direction(snake, -1, 0);
            break;
        case KEY_RIGHT:
        case 'd':
            set_snake_direction(snake, 1, 0);
            break;
        default:
            break;
    }
}

void update(float deltaTime) {
    for (int i = 0; i < MAX_ENTITIES; i++) {
        Entity *entity = entities[i];
        if (entity && entity->update) {
            entity->update(entity);
        }
    }
}

void render() {
    // render entities
    for (int i = 0; i < MAX_ENTITIES; i++) {
        Entity *entity = entities[i];
        if (entity && entity->render) {
            entity->render(entity);
        }
    }
}

void render_gui(Game *game) {
    // combine score string with score int
    sprintf(game->score_string, "%s%d", get_localized_text("score_text"),
            game->score);
    draw_text(game->score_string, 2, 25);
    draw_text(get_localized_text("snake_description"), 20, 25);
}

void shutdown() {
    free_snake(snake);

    for (int i = 0; i < MAX_ENTITIES; i++) {
        free(entities[i]);
    }

    endwin();
}
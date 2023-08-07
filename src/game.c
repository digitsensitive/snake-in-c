#include "game.h"

#include <stdlib.h>
#include <time.h>

#include "clock.h"
#include "entities/apple.h"
#include "entities/snake.h"
#include "languages.h"
#include "ncurses/ncurses_utils.h"
#include "ncurses/ncurses_window.h"
#include "utils.h"

// Entities
Snake* snake;
Apple* apple;

// Variables
int score = 0;
char score_string[30];
bool is_running = true;

int init() {
    if (!init_ncurses_window()) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return 0;
    }

    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(main_window, true);

    // disable input blocking (f.e. for getch() and wgetch())
    nodelay(main_window, true);

    // set the cursor mode to "Invisible"
    curs_set(0);

    // init colors for the terminal
    if (!init_colors()) {
        endwin();
        return 0;
    }

    // resize the game field
    resize_term(WINDOW_HEIGHT, WINDOW_WIDTH);

    // draw a box around the screen
    box(main_window, 0, 0);

    // resize the window to fit text at the bottom
    resize_term(WINDOW_HEIGHT + 1, WINDOW_WIDTH);

    // Seed the random number generator with the current time
    srand(time(NULL));

    return 1;
}

void run() {
    // set language
    set_language(EN);

    snake = create_snake('X', 10, 5);
    apple = create_apple('O', 20, 10);

    while (is_running) {
        input();

        // Calculate time elapsed since the last iteration
        calculate_time_elapsed();

        // Update the game state based on time elapsed
        update(get_delta_time());

        // Render
        render();

        // Delay to achieve the desired FPS
        delay_clock();

        refresh();
    }

    free_snake(snake);
    free(snake);
}

void input() {
    int in_char = wgetch(main_window);

    switch (in_char) {
        case 'q':
            is_running = false;
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
    update_apple(apple);
    update_snake(snake);
    check_for_collisions();
    is_outside_boundary();
}

void render() {
    render_apple(apple);
    render_snake(snake);
    render_gui();
}

void render_gui() {
    // combine score string with score int
    sprintf(score_string, "%s%d", get_localized_text("score_text"), score);

    draw_text(score_string, 2, 25);
    draw_text(get_localized_text("snake_description"), 20, 25);
}

void check_for_collisions() {
    if (snake_hit_snake(snake)) {
        is_running = false;
        printf("You score is: %d", score);
    }

    if (apple->pos.x == snake->body->pos.x &&
        apple->pos.y == snake->body->pos.y) {
        // collision between snake and apple occured
        // add one point to the score
        score += 1;

        // set new random position for the apple
        reset_apple_position(apple);

        // grow snake
        is_growing(snake);
    }
}

void is_outside_boundary() {
    int x = snake->body->pos.x;
    int y = snake->body->pos.y;

    if (x < 1 || x > (WINDOW_WIDTH - 2) || y < 1 || y > WINDOW_HEIGHT - 2) {
        is_running = false;
        printf("You score is: %d", score);
    }
}

void shutdown() { endwin(); }
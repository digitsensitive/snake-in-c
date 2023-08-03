#include "game.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#include "constants.h"

// Game loop frequency in frames per second
#define FPS 10
#define FRAME_TIME_MS (1000 / FPS)

// Entities
Snake* snake;
Apple* apple;

// Variables
int score = 0;

// Variables for time measurement
clock_t currentTime, previousTime;
float deltaTime;

WINDOW* wnd;
bool is_running = true;

int init() {
    if ((wnd = initscr()) == NULL) {
        fprintf(stderr, "Error initializing ncurses.\n");
        return 0;
    }

    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(wnd, true);

    // disable input blocking (f.e. for getch() and wgetch())
    nodelay(wnd, true);

    // set the cursor mode to "Invisible"
    curs_set(0);

    if (!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support Color.\n");
        return 0;
    }

    // init use of colors on terminal
    start_color();

    // resize the game field
    resize_term(GAME_HEIGHT, GAME_WIDTH);

    // draw a box around the screen
    box(wnd, 0, 0);

    return 1;
}

void run() {
    snake = create_snake(10, 5);
    apple = create_apple(20, 10);

    while (is_running) {
        input();

        // Calculate time elapsed since the last iteration
        currentTime = clock();
        deltaTime = (float)(currentTime - previousTime) / CLOCKS_PER_SEC;
        previousTime = currentTime;

        // Update the game state based on time elapsed
        update(deltaTime);
        render();

        // Delay to achieve the desired FPS
        napms(FRAME_TIME_MS);

        refresh();
    }

    free(snake);
}

void input() {
    int in_char = wgetch(wnd);

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
    char* greetings = "Snake written in C for the Terminal. ";
    char* scoreText = "Score: ";
    char combinedString[100];  // Choose an appropriate buffer size
    sprintf(combinedString, "%s%d", scoreText, score);
    mvprintw(24, 2, "%s", combinedString);
    mvprintw(24, 30, "%s", greetings);
}

void check_for_collisions() {
    if (apple->base.pos.x == snake->base.pos.x &&
        apple->base.pos.y == snake->base.pos.y) {
        // collision between snake and apple occured
        // add one point to the score
        score += 1;

        // set new random position for the apple
        reset_apple_position(apple);

        // grow snake by 1
        grow_snake(snake, 1);
    }
}

void is_outside_boundary() {
    int x = snake->base.pos.x;
    int y = snake->base.pos.y;

    if (x < 1 || x > GAME_WIDTH - 1 || y < 1 || y > GAME_HEIGHT - 1) {
        is_running = false;
        printf("You score is: %d", score);
    }
}

void shutdown() { endwin(); }
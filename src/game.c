#include "game.h"

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

// Game loop frequency in frames per second
#define FPS 30
#define FRAME_TIME_MS (1000 / FPS)
#define DESIRED_WIDTH 70
#define DESIRED_HEIGHT 25

// add entities
Snake* snake;
Apple* apple;

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

    // Get the current number of rows and columns
    int g_height, g_width;
    getmaxyx(wnd, g_height, g_width);

    g_width = g_width < DESIRED_WIDTH ? g_width : DESIRED_WIDTH;
    g_height = g_height < DESIRED_HEIGHT ? g_height : DESIRED_HEIGHT;

    // draw box around screen
    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);

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
}

void render() {
    render_apple(apple);
    render_snake(snake);
}

void shutdown() { endwin(); }
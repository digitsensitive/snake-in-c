#include <stdio.h>
#include <stdlib.h>

#include "game.h"

int main(int argc, char **argv) {
    Game *game = init_game();

    if (game == NULL) {
        fprintf(stderr, "Error initializing game instance.\n");
        return 0;
    }

    while (game->is_running) {
        run_game(game);
    }

    shutdown();

    free(game);

    return 0;
}
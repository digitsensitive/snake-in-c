#include "game.h"

int main(int argc, char **argv) {
    int init_status = init();

    if (init_status == 1) {
        run();
    }

    shutdown();

    return 0;
}
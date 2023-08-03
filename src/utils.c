#include <stdlib.h>

#include "constants.h"

// Function to generate a random integer between min and max (inclusive)
int get_random_int(int min, int max) {
    if (min > max) {
        // Swap min and max if they are in the wrong order
        int temp = min;
        min = max;
        max = temp;
    }
    return (rand() % (max - min + 1)) + min;
}
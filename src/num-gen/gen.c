#include "gen.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *gen(int num_digits) {
    int *res = malloc(num_digits * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < num_digits; i++) {
        res[i] = rand() % 10;
    }

    return res;
}

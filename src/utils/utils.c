#include "utils.h"
#include <stdio.h>
#include <unistd.h>

void hideCursor() { printf("\33[?25l"); }

void showCursor() { printf("\33[?25h"); }

void printArr(int arr[], int num_digits) {
    for (int i = 0; i < num_digits; i++) {
        printf("%d", arr[i]);
    }

    printf("\n");

    fflush(stdout);
}

void clearLines(int num_lines, int sleep_duration) {
    fflush(stdout);
    sleep(sleep_duration);
    for (int i = 1; i < num_lines; i++) {
        printf("\x1b[1F"); // Move to beginning of previous line
        printf("\x1b[2K"); // Clear entire line
    }

    printf("\x1b[2K"); // Clear entire line
}

void createCountdown(int countdown_length) {
    hideCursor();
    printf("\n\n");
    for (int i = countdown_length; i > 0; i--) {
        printf("\rHiding in %d seconds", i);
        clearLines(0, 1); }
    clearLines(4, 0);
    showCursor();
}

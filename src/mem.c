#include "./num-gen/gen.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int *gen(int num_digits) {
    int *res = malloc(num_digits * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < num_digits; i++) {
        res[i] = rand() % 10;
    }

    return res;
}

void printArr(int arr[], int num_digits) {
    for (int i = 0; i < num_digits; i++) {
        printf("%d", arr[i]);
    }

    printf("\n");

    fflush(stdout);
}

void hideCursor() { printf("\33[?25l"); }

void showCursor() { printf("\33[?25h"); }

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

int *getUserAnswer(int num_digits, int *err) {
    int *ans = malloc(num_digits * sizeof(int));

    char c;
    int curr_length = 0;

    printf("Please enter you answer below:\n\n");

    while ((c = fgetc(stdin)) != EOF && curr_length < num_digits) {
        if (c == '\n') {
            break;
        }

        if (c < '0' || c > '9') {
            fprintf(stderr, "Only numbers are accepted as valid input comrade. %d\n",
                    c);
            *err = 1;
            return err;
        }

        ans[curr_length] = atoi(&c);

        curr_length++;
    }

    if (curr_length != num_digits) {
        fprintf(stderr, "Your answer length is incorrect comrade.\n");
        *err = 1;
        return err;
    }

    return ans;
}

int checkUserAnswerCorrect(int answer[], int input[], int num_digits) {
    for (int i = 0; i < num_digits; i++) {
        if (answer[i] != input[i]) {
            printf("Incorrect answer comrade.\n");
            return 0;
        }
    }

    printf("Correct answer comrade.\n");
    return 1;
}

void createWaitingBuffer(int buffer_duration) {
    hideCursor();
    printf("\n");
    for (int i = buffer_duration; i > 0; i--) {
        printf("\rPlease wait for %d seconds", i);
        clearLines(0, 1);
    }

    clearLines(2, 0);
    showCursor();
}

int main() {
    int num_digits = 3;
    int countdown_length = 2;
    int buffer_duration = 2;

    int chances = 3;
    int err = 0;
    int currQuestion = 1;

    while (chances > 0) {
        int *answer = gen(num_digits);
        printArr(answer, num_digits);
        createCountdown(countdown_length);

        printf("You have %d chances remaining. You are on question %d.\n",
                chances, currQuestion);
        clearLines(2, buffer_duration);

        int *input = getUserAnswer(num_digits, &err);

        if (err == 1) {
            clearLines(5, 1);

            chances -= 1;
            continue;
        }

        int res = checkUserAnswerCorrect(answer, input, num_digits);

        if (res == 0) {
            chances -= 1;
        }

        currQuestion += res;

        clearLines(5, 1);
    }

    printf("You answered %d questions comrade.", currQuestion - 1);

    return 0;
}

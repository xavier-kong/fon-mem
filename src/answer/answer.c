#include "answer.h"
#include <stdio.h>
#include <stdlib.h>

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
            fprintf(stderr,
                    "Only numbers are accepted as valid input comrade.\n");
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


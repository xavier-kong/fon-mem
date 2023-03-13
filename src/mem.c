#include "./answer/answer.h"
#include "./num-gen/gen.h"
#include "./utils/utils.h"
#include <stdio.h>

int main() {
    int num_digits = 1;
    int countdown_length = 2;
    int *buffer_duration = &num_digits;

    int chances = 3;
    int err = 0;
    int currQuestion = 1;

    while (chances > 0) {
        int *answer = gen(num_digits);
        printArr(answer, num_digits);
        createCountdown(countdown_length);

        printf("You have %d chances remaining. You are on question %d.\n", chances,
                currQuestion);
        clearLines(2, *buffer_duration);

        int *input = getUserAnswer(num_digits, &err);

        if (err == 1) {
            clearLines(5, 1);

            chances -= 1;
            continue;
        }

        int res = checkUserAnswerCorrect(answer, input, num_digits);

        if (res == 0) {
            chances -= 1;
            if (num_digits > 1) {
                num_digits--;
            }
        } else {
            num_digits++;
        }

        currQuestion += res;

        clearLines(5, 1);
    }

    printf("You answered %d questions comrade.", currQuestion - 1);

    return 0;
}

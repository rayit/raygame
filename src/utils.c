#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int GenerateQuestion(char *out) {
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    sprintf(out, "%d + %d = ?", a, b);
    return a + b;
}


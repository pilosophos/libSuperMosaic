#include <stdio.h>
#include "../src/vec2.h"

int add() {
    vec2 vecA = {x: 1, y: 2};
    vec2 vecB = {x: 3, y: 4};

    vec2Add(&vecA, &vecB);

    if (vecA.x != 4 || vecA.y != 6) {
        printf("FAILED: add() expected (4, 6), got (%d, %d)\n", vecA.x, vecA.y);
        return 1;
    }

    return 0;
}

int main() {
    int failed = 0;

    failed += add();

    printf("Failing tests: %d\n", failed);

    return 0;
}
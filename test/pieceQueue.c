#include <stdio.h>
#include "../src/pieceQueue.h"

/** Test if every 7 pieces popped from the queue contains 1 of each tetromino */
int queueGeneratesRandomBag() {
    const int expectedSum = 21; // since piece shapes are enum values 0-6, the sum of all of them is 21

    pieceQueue* queue = newPieceQueue();

    int sum = 0;
    for (int i = 0; i < PIECE_SUBQUEUE_LENGTH*10; i++) {
        unplacedPiece* next = popPieceQueue(queue);

        sum += next->basicShape;

        if (i+1 % 7 == 0) {
            if (sum != expectedSum) {
                printf("FAILED: queueGeneratesRandomBag() did not receive one of each tetromino shape in 7 pops: expected %d, got %d\n", expectedSum, sum);
                return 1;
            }
            sum = 0;
        }
    }

    return 0;
}

int main() {
    int failed = 0;

    failed += queueGeneratesRandomBag();

    printf("Failing tests: %d\n", failed);

    return 0;
}
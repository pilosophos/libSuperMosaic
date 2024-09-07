#include <stdlib.h>
#include "pieceQueue.h"

void swapSubQueues(pieceQueue* queue) {
    unplacedPiece** temp = queue->forwardQueue;
    queue->forwardQueue = queue->backQueue;
    queue->backQueue = temp;

    queue->currentIndex = 0;
}

void shuffle(int *array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void refreshSubQueue(unplacedPiece** subQueue) {
    basicShape* possibleShapes[PIECE_QUEUE_LENGTH] = {
        SHAPE_I,
        SHAPE_O,
        SHAPE_T,
        SHAPE_L,
        SHAPE_J,
        SHAPE_S,
        SHAPE_Z
    };
    shuffle(possibleShapes, PIECE_QUEUE_LENGTH);

    for (int i = 0; i < PIECE_QUEUE_LENGTH; i++) {
        vec2 originXY = {x: 0, y: 0};
        subQueue[i] = newPiece(originXY, possibleShapes[i], rand() % 4);
    }
}

unplacedPiece* popPieceQueue(pieceQueue* queue) {
    unplacedPiece* front = queue->forwardQueue[queue->currentIndex];

    queue->currentIndex++;
    if (queue->currentIndex > PIECE_QUEUE_LENGTH) {
        swapSubQueues(queue);
        refreshSubQueue(queue->forwardQueue);
    }

    return front;
}
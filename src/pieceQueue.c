#include <stdlib.h>
#include "pieceQueue.h"

void swapSubQueues(pieceQueue* queue) {
    unplacedPiece** temp = queue->forwardQueue;
    queue->forwardQueue = queue->backQueue;
    queue->backQueue = temp;

    queue->currentIndex = 0;
}

void shuffle(basicShape* array, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          basicShape t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

void refreshSubQueue(unplacedPiece** subQueue) {
    basicShape possibleShapes[PIECE_SUBQUEUE_LENGTH] = {
        SHAPE_I,
        SHAPE_O,
        SHAPE_T,
        SHAPE_L,
        SHAPE_J,
        SHAPE_S,
        SHAPE_Z
    };
    shuffle(possibleShapes, PIECE_SUBQUEUE_LENGTH);

    for (int i = 0; i < PIECE_SUBQUEUE_LENGTH; i++) {
        vec2 originXY = {x: 0, y: 0};
        subQueue[i] = newPiece(originXY, possibleShapes[i], rand() % 4);
    }
}

pieceQueue* newPieceQueue() {
    pieceQueue* newQueue = malloc(sizeof(pieceQueue));
    newQueue->currentIndex = 0;

    // init front queue
    unplacedPiece** forwardQueue = malloc(sizeof(unplacedPiece*) * PIECE_SUBQUEUE_LENGTH);
    newQueue->forwardQueue = forwardQueue;
    refreshSubQueue(forwardQueue);

    // init back queue
    unplacedPiece** backQueue = malloc(sizeof(unplacedPiece*) * PIECE_SUBQUEUE_LENGTH);
    newQueue->backQueue = backQueue;
    refreshSubQueue(backQueue);

    return newQueue;
}

void destroyPieceQueue(pieceQueue* queue) {
    free(queue->forwardQueue);
    free(queue->backQueue);
    free(queue);
}

unplacedPiece* popPieceQueue(pieceQueue* queue) {
    unplacedPiece* front = queue->forwardQueue[queue->currentIndex];

    queue->currentIndex++;
    if (queue->currentIndex >= PIECE_SUBQUEUE_LENGTH) {
        swapSubQueues(queue);
        refreshSubQueue(queue->forwardQueue);
    }

    return front;
}
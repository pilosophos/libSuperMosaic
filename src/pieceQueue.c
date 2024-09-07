#include "pieceQueue.h"

void swapSubQueues(pieceQueue* queue) {
    unplacedPiece** temp = queue->forwardQueue;
    queue->forwardQueue = queue->backQueue;
    queue->backQueue = temp;

    queue->currentIndex = 0;
}

void refreshSubQueue(unplacedPiece** subQueue) {
    for (int i = 0; i < PIECE_QUEUE_LENGTH; i++) {
        // TODO: implement me
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
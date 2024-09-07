#include "unplacedPiece.h"

#ifndef LSM_PIECE_QUEUE_H
#define LSM_PIECE_QUEUE_H

/**
 * Length of the individual forward and back queues. Should hold enough for one
 * of every tetromino per queue.
 * 
 * In the future, I might make this configurable by the front-end, to support
 * one of every <tetromino, rotation> combo.
 */
const int PIECE_SUBQUEUE_LENGTH = 7;

/**
 * Unplaced pieces in the NEXT queue.
 * 
 * The queue is double buffered (that is,
 * it has both forward and back sub-queues) in order to allow the front-end
 * to always preview at least 7 tetrominos ahead while still using the
 * random-bag selection strategy, where every 7 tetrominos generated contain
 * one of each tetromino shape.
 */
typedef struct pieceQueue {
    /** The index of the front of the queue */
    int currentIndex;

    /**
     * Array of pointers to pieces in the forward queue. The NEXT piece will
     * always be at the `pieceQueue.currentIndex` of the forward queue.
     * 
     * If more pieces need to be previewed than remain in the forward queue, the
     * front-end should look in the back queue, which comes directly after the
     * forward queue.
     */
    unplacedPiece** forwardQueue;

    /**
     * Array of pointers to pieces in the back queue
     * Replaces the forwardQueue when end of the forward queue has been reached.
     */
    unplacedPiece** backQueue;
} pieceQueue;

pieceQueue* newPieceQueue();
void destroyPieceQueue(pieceQueue* queue);

unplacedPiece* popPieceQueue(pieceQueue* queue);

#endif
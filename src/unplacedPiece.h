#include "vec2.h"
#include "block.h"

#ifndef LSM_UNPLACED_PIECE_H
#define LSM_UNPLACED_PIECE_H

typedef enum {
    SHAPE_I,
    SHAPE_O,
    SHAPE_T,
    SHAPE_L,
    SHAPE_J,
    SHAPE_S,
    SHAPE_Z
} pieceShape;

/**
 * @brief An unplaced piece, including those in the piece queue.
 */
typedef struct unplacedPiece {
    /** Global top left XY */
    vec2* topLeftXY;
    /** XYs of the four tetromino blocks, relative to the piece's top left corner */
    vec2 blockRelativeXYs[4];

    /** The block that this piece is made of */
    block block;

    /** private */
    unsigned char width;
    unsigned char height;
} unplacedPiece;

unplacedPiece newUnplacedPiece(pieceShape shape, vec2* topLeftXY);
void rotatePiece(unplacedPiece* piece, int times);
void translatePiece(unplacedPiece* piece, vec2 amount);

#endif

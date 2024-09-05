#include <stdint.h>
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
} basicShape;

/**
 * @brief Bitwise-encoded position of a piece's blocks on a 4x4 grid.
 * (See: https://stackoverflow.com/a/38596291)
 */
typedef int16_t shapeBits;

/**
 * @brief An unplaced piece, including those in the piece queue.
 */
typedef struct unplacedPiece {
    /** Global top left XY */
    vec2* topLeftXY;

    /** This piece's basic Tetromino shape */
    basicShape basicShape;

    /** This piece's rotation (number of times rotated) */
    unsigned char rotation;
} unplacedPiece;

void rotatePiece(unplacedPiece* piece, unsigned char times);
void translatePiece(unplacedPiece* piece, vec2* amount);

/**
 * @brief Get the bits representing where this piece's blocks are
 * 
 * @param piece Piece to get block bits of
 * @return shapeBits Block bits
 */
shapeBits getPieceBlockBits(unplacedPiece* piece);

#endif

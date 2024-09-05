#include "unplacedPiece.h"

/**
 * @brief List of shapeBits for all rotations of each basic Tetromino shape
 * 
 * Ex: `shapeHexes[SHAPE_S][2]` gets the S Tetromino rotated twice.
 */
shapeBits shapeHexes[8][4] = {
  { 0x0F00, 0x4444, 0x0F00, 0x4444 }, // I
  { 0xCC00, 0xCC00, 0xCC00, 0xCC00 }, // O
  { 0x0E40, 0x4C40, 0x4E00, 0x4640 }, // T
  { 0xE800, 0xC440, 0x2E00, 0x88C0 }, // L
  { 0xE200, 0x44C0, 0x8E00, 0xC880 }, // J
  { 0x6C00, 0x8C40, 0x6C00, 0x8C40 }, // S
  { 0x4C80, 0xC600, 0x4C80, 0xC600 }, // Z
};

void rotatePiece(unplacedPiece* piece, unsigned char times) {
    piece->rotation = piece->rotation + times % 4;
}

void translatePiece(unplacedPiece* piece, vec2* amount) {
    vec2Add(piece->topLeftXY, amount);
}

shapeBits getPieceBlockBits(unplacedPiece* piece) {
    return shapeHexes[piece->basicShape][piece->rotation];
}
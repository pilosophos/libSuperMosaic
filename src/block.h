/**
 * @file block.h
 * @brief Data structures for representing a single block.
 */

#ifndef LSM_BLOCK_H
#define LSM_BLOCK_H

/**
 * @brief Possible block types. Used for coloring blocks.
 * 
 * @note IF YOU CHANGE THE ORDER OF THE BLOCKS you also need to change `unplacedPiece.c#shapeHexes`
 */
typedef enum {
    BLOCK_I,
    BLOCK_O,
    BLOCK_T,
    BLOCK_L,
    BLOCK_J,
    BLOCK_S,
    BLOCK_Z,
    BLOCK_OTHER
} block;

#endif
/**
 * @file block.h
 * @brief Data structures for representing a single block.
 */

#ifndef LSM_BLOCK_H
#define LSM_BLOCK_H

/**
 * @brief Possible origins for blocks.
 */
typedef enum {
    OTHER,
    I,
    O,
    T,
    L,
    J,
    S,
    Z
} blockOrigin;

/**
 * @brief A single block.
 */
typedef struct block {
    /** Origin on this block. May be used by front-ends for block coloring. */
    blockOrigin blockOrigin;
} block;

#endif
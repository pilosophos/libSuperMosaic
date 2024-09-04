/**
 * @file block.h
 * @brief Data structures for representing a single block.
 */

#ifndef LSM_BLOCK_H
#define LSM_BLOCK_H

/**
 * @brief Possible block types. Used for coloring blocks.
 */
typedef enum {
    BLOCK_OTHER,
    BLOCK_I,
    BLOCK_O,
    BLOCK_T,
    BLOCK_L,
    BLOCK_J,
    BLOCK_S,
    BLOCK_Z
} block;

#endif
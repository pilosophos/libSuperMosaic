/**
 * @file action.h
 * @brief Defines the action enum.
 */

#ifndef LSM_ACTION_H
#define LSM_ACTION_H

/**
 * @brief Possible user actions, such as drops, clearing single lines, etc.
 */
typedef enum {
    SOFT_DROP,
    DROP,
    SINGLE,
    DOUBLE,
    TRIPLE,
    QUAD,
    MOSAIC
} action;

#endif
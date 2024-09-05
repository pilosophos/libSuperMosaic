/**
 * @file action.h
 * @brief Defines the action enum representing user actions like drops and line
 * clears.
 */

#ifndef LSM_ACTION_H
#define LSM_ACTION_H

/**
 * @brief Possible user actions, such as drops, clearing single lines, etc.
 */
typedef enum {
    ACTION_SOFT_DROP,
    ACTION_HARD_DROP,
    ACTION_SINGLE,
    ACTION_DOUBLE,
    ACTION_TRIPLE,
    ACTION_QUAD,
    ACTION_MOSAIC
} action;

#endif
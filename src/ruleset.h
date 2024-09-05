/**
 * @file ruleset.h
 * @brief Defines the ruleset struct, an interface for implementing different
 * game rules.
 */

#include "action.h"

#ifndef LSM_RULESET_H
#define LSM_RULESET_H

/**
 * @brief Each ruleset defines rules that can be changed each game. This allows
 * you to customize board size, leveling behavior, action scoring, etc.
 * 
 * For example, since the classic variant of the game has no leveling system and
 * a constant forced drop timeout of 4 game ticks, getLevel could always return
 * 1 and getDropTimeout could always return 4.
 */
typedef struct ruleset {
    /** Board height */
    int height;
    /** Board width */
    int width;

    /** 1/true if the next piece should appear where the last piece dropped */
    int dynamicCursor;

    /** Get the level based on the total number of lines cleared */
    int (*getLevel)(int /* linesCleared */);

    /** Get the drop timeout in number of game ticks, based on level */
    int (*getDropTimeout)(int /* level */);

    /**
     * Get the score of an action, based on level, the current simple clear
     * chain, and the current difficult clear chain
     */
    int (*scoreAction)(
        action,
        int /* level */,
        int /* chain */,
        int /* difficultChain */
    );

} ruleset;

#endif
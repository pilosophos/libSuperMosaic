/**
 * @file classic.h
 * @brief Reference implementation of the Classic ruleset:
 * - 10x20 board
 * - No dynamic cursor
 * - Constant level
 * - 4 tick constant forced drop timeout
 * - Classic scoring
 */

#include "../ruleset.h"

#ifndef LSM_RULESET_CLASSIC_H
#define LSM_RULESET_CLASSIC_H

int getLevelClassic(int linesCleared);
int getDropTimeoutClassic(int level);
int scoreActionClassic(action action, int level, int timeLeft, int chain, int difficultChain);

extern ruleset classicRuleset = {
    height: 20,
    width: 10,
    isHoldAllowed: 0,
    dynamicCursor: 0,
    getLevel: &getLevelClassic,
    getDropTimeout: &getDropTimeoutClassic,
    scoreAction: &scoreActionClassic
};

#endif
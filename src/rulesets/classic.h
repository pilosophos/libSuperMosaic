#include "../ruleset.h"

#ifndef LSM_RULESET_CLASSIC_H
#define LSM_RULESET_CLASSIC_H

int getLevelClassic(int linesCleared);
int getDropTimeoutClassic(int level);
int scoreActionClassic(action action, int level, int chain, int difficultChain);

extern ruleset classicRuleset = {
    height: 20,
    width: 10,
    dynamicCursor: 0,
    getLevel: &getLevelClassic,
    getDropTimeout: &getDropTimeoutClassic,
    scoreAction: &scoreActionClassic
};

#endif
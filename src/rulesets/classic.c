#include "classic.h"

int getLevelClassic(int linesCleared) {
    return 1;
}

int getDropTimeoutClassic(int level) {
    return 4;
}

int scoreActionClassic(action action, int level, int timeLeft, int chain, int difficultChain) {
    int score = 0;

    if (timeLeft > 0) {
        score = 2 * (timeLeft + 1);
    }

    switch (action)
    {
        case ACTION_SINGLE: return score + 100;
        case ACTION_DOUBLE: return score + 300;
        case ACTION_TRIPLE: return score + 500;
        case ACTION_QUAD: return score + 800;
        case ACTION_MOSAIC: return score + 1100;
        default: return score;
    }
}
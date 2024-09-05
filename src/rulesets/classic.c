#include "classic.h"

int getLevelClassic(int linesCleared) {
    return 1;
}

int getDropTimeoutClassic(int level) {
    return 4;
}

int scoreActionClassic(action action, int level, int timeLeft, int chain, int difficultChain) {
    switch (action)
    {
        case ACTION_SOFT_DROP: return 0;
        case ACTION_HARD_DROP: return 2 * (timeLeft + 1);
        case ACTION_SINGLE: return 100;
        case ACTION_DOUBLE: return 300;
        case ACTION_TRIPLE: return 500;
        case ACTION_QUAD: return 800;
        case ACTION_MOSAIC: return 1100;
    }
}
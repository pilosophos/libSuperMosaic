#include "input.h"
#include "pieceQueue.h"
#include "ruleset.h"

#ifndef LSM_GAME_H
#define LSM_GAME_H

typedef struct game {
    ruleset* ruleset;

    int isGameOver;
    int linesCleared;
    int totalScore;
    int chain;
    int difficultChain;

    int forcedDropTimeoutTicks;
    block** placedBlocks;
    pieceQueue* pieceQueue;
    unplacedPiece* hoveringPiece;
    unplacedPiece* heldPiece;
    vec2 cursor;
} game;

game* newGame(ruleset* ruleset);
void destroyGame(game* game);

action tickGame(game* game);
action handleGameInput(game* game, input input);

#endif
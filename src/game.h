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

    /** Time until the game forces a soft drop, in ticks */
    int forcedDropTimeoutTicks;
    /** Board of placed blocks. (0,0) is at the top left corner. */
    block** placedBlocks;
    /** Queue of upcoming pieces */
    pieceQueue* pieceQueue;
    /** The currently hovering piece */
    unplacedPiece* hoveringPiece;
    /** Where the next piece should spawn in */
    vec2 cursor;

    /** 1/true if the user used up their hold */
    int isHoldUsed;
    /** The currently held piece, or NULL if none is held */
    unplacedPiece* heldPiece;
} game;

game* newGame(ruleset* ruleset);
void destroyGame(game* game);

action tickGame(game* game);
action handleGameInput(game* game, input input);

#endif
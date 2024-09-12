#include <stdio.h>
#include "game.h"

game* newGame(ruleset* ruleset) {
    game* game = malloc(sizeof(game));

    game->ruleset = ruleset;

    game->isGameOver = 0;
    game->linesCleared = 0;
    game->totalScore = 0;
    game->chain = 0;
    game->difficultChain = 0;

    game->forcedDropTimeoutTicks = ruleset->getDropTimeout(0);
    game->placedBlocks = malloc(sizeof(block) * ruleset->height * ruleset->width);
    game->pieceQueue = newPieceQueue();
    game->hoveringPiece = popPieceQueue(game->pieceQueue);
    game->heldPiece = NULL;

    vec2 cursor = {x: 0, y: 0};
    game->cursor = cursor;

    return game;
}

void destroyGame(game* game) {
    destroyPieceQueue(game->pieceQueue);
    destroyPiece(game->hoveringPiece);
    destroyPiece(game->heldPiece);
    free(game->placedBlocks);
    free(game);
}
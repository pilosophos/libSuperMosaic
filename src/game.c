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

    vec2 cursor = {x: 0, y: 0};
    game->cursor = cursor;

    game->canHold = 1;
    game->heldPiece = NULL;

    return game;
}

void destroyGame(game* game) {
    destroyPieceQueue(game->pieceQueue);
    destroyPiece(game->hoveringPiece);
    destroyPiece(game->heldPiece);
    free(game->placedBlocks);
    free(game);
}

action tickGame(game* game) {
    game->forcedDropTimeoutTicks--;

    if (game->forcedDropTimeoutTicks == 0) {
        int isPlaceOk = placePiece(game);
        if (!isPlaceOk) {
            game->isGameOver = 1;
            return ACTION_GAME_OVER;
        }

        int clearedLines = clearFullLines(game);
        action action = updateGameStatistics(game, clearedLines, ACTION_SOFT_DROP);
        
        game->hoveringPiece = popPieceQueue(game->pieceQueue);
        return action;
    }

    return ACTION_NONE;
}

action handleGameInput(game* game, input input) {
    int isPlaceOk = placePiece(game);
    if (!isPlaceOk) {
        return ACTION_NONE;
    }

    // TODO: implement me
}

/**
 * @brief Updates the game statistics based on the number of cleared lines
 * 
 * @param game The game to update
 * @param clearedLines The number of lines cleared by the drop
 * @param dropAction ACTION_SOFT_DROP or ACTION_HARD_DROP, depending on what caused this to run
 * @return Same as dropAction if no lines cleared, otherwise the appropriate line clear action
 */
action updateGameStatistics(game* game, int clearedLines, action dropAction) {
    action action = dropAction;
    switch (clearedLines) {
        case 1: action = ACTION_SINGLE; break;
        case 2: action = ACTION_DOUBLE; break;
        case 3: action = ACTION_TRIPLE; break;
        case 4: action = ACTION_QUAD; break;
        case 5: action = ACTION_MOSAIC; break;
    }

    // update normal and difficult chains
    if (clearedLines == 0) {
        game->chain = 0;
        game->difficultChain = 0;
    } else {
        game->chain++;
        if (clearedLines >= 4) {
           game->difficultChain++;
        }
    }

    // update linesCleared and totalScore
    game->linesCleared += clearedLines;
    game->totalScore += game->ruleset->scoreAction(
        action,
        game->ruleset->getLevel(game->linesCleared),
        game->forcedDropTimeoutTicks,
        game->chain,
        game->difficultChain
    );

    return action;
}

/**
 * @brief Try placing the active piece on the board.
 * 
 * @param game Game to update
 * @return 1 if the piece placed successfully, 0 if there's something in the way
 */
int placePiece(game* game) {
    // TODO: implement me
    return 0;
}

/**
 * @brief Detect any full lines and clear them.
 * 
 * @param game Game to update
 * @return Number of cleared lines.
 */
int clearFullLines(game* game) {
    // TODO: implement me
    return 0;
}
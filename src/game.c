#include <stdlib.h>
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
    game->placedBlocks = malloc(sizeof(block) * ruleset->height * ruleset->width); // TODO: this needs to be filled with BLOCK_NONE after init
    game->pieceQueue = newPieceQueue();
    game->hoveringPiece = popPieceQueue(game->pieceQueue);

    vec2 cursor = {x: game->ruleset->width / 2, y: game->ruleset->height / 2};
    game->cursor = cursor;

    game->isHoldUsed = 0;
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

block getBlockAt(block* board, int boardWidth, int boardHeight, int x, int y) {
    return board[(y * boardWidth) + (sizeof(block) * x)];
}

block setBlockAt(block* board, int boardWidth, int boardHeight, int x, int y, block newBlock) {
    board[(y * boardWidth) + (sizeof(block) * x)] = newBlock;
}

/**
 * @brief Try placing the active piece on the board.
 * 
 * @param board Board to place on
 * @param piece Piece to place
 * @return 1 if the piece placed successfully, 0 if there's something in the way
 */
int placePiece(block* board, int boardWidth, int boardHeight, unplacedPiece* piece) {
    // scan for blocks in the way
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (getBlockAt(board, boardWidth, boardHeight, x, y) != BLOCK_NONE) {
                return 0;
            }
        }
    }

    // place blocks
    block block = getBlockForShape(piece->basicShape); // TODO: implement this function
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            setBlockAt(board, boardWidth, boardHeight, x, y, block);
        }
    }

    return 1;
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

int isPieceOutOfBounds(unplacedPiece* piece, vec2 atLocation, int boardWidth, int boardHeight) {
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (xyHasBlock(piece, x + atLocation.x, y + atLocation.y)) {
                if ((x < 0 || x >= boardWidth) || (y < 0 || y >= boardHeight)) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

action tickGame(game* game) {
    game->forcedDropTimeoutTicks--;

    if (game->forcedDropTimeoutTicks == 0) {
        int isPlaceOk = placePiece(
            game->placedBlocks,
            game->ruleset->width,
            game->ruleset->height,
            game->hoveringPiece
        );
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
    if (input == INPUT_HARD_DROP) {
        int isPlaceOk = placePiece(
            game->placedBlocks,
            game->ruleset->width,
            game->ruleset->height,
            game->hoveringPiece
        );
        if (!isPlaceOk) {
            return ACTION_NONE;
        }

        int clearedLines = clearFullLines(game);
        action action = updateGameStatistics(game, clearedLines, ACTION_HARD_DROP);
        game->hoveringPiece = popPieceQueue(game->pieceQueue);
        return action;
    }

    if (input == INPUT_HOLD) {
        if (game->ruleset->isHoldAllowed && !game->isHoldUsed) {
            int level = game->ruleset->getLevel(game->linesCleared);
            game->forcedDropTimeoutTicks = game->ruleset->getDropTimeout(level);

            if (game->heldPiece) {
                unplacedPiece* temp = game->heldPiece;
                game->heldPiece = game->hoveringPiece;
                game->heldPiece = temp;
            } else {
                game->heldPiece = game->hoveringPiece;
                game->hoveringPiece = popPieceQueue(game->pieceQueue);
            }

            game->isHoldUsed = 0;
        }
        return ACTION_NONE;
    }

    if (input == INPUT_UP || input == INPUT_DOWN || input == INPUT_LEFT || input == INPUT_RIGHT) {
        vec2 delta;
        switch (input)
        {
            case INPUT_UP: delta = (vec2){x: 0, y: -1}; break;
            case INPUT_DOWN: delta = (vec2){x: 0, y: 1}; break;
            case INPUT_LEFT: delta = (vec2){x: -1, y: 0}; break;
            case INPUT_RIGHT: delta = (vec2){x: 1, y: 0}; break;
        }

        vec2 destination = vec2Add(game->hoveringPiece->topLeftXY, delta);

        int isOutOfBounds = isPieceOutOfBounds(
            game->hoveringPiece,
            destination,
            game->ruleset->width,
            game->ruleset->height
        );
        if (isOutOfBounds) {
            return ACTION_NONE;
        }

        game->hoveringPiece->topLeftXY = destination;
        return ACTION_MOVE;
    }
}
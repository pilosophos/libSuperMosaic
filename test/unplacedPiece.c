#include <stdio.h>
#include "../src/unplacedPiece.h"

int main() {
    vec2 globalXY = {x: 0, y: 0};
    unplacedPiece piece = {
        topLeftXY: &globalXY,
        basicShape: SHAPE_Z,
        rotation: 3
    };

    rotatePiece(&piece, 16);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (xyHasBlock(&piece, x, y)) {
                printf("x");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}
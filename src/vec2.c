#include "vec2.h"

vec2 newVec2(int x, int y){
    vec2 vector;
    vector.x = x;
    vector.y = y;

    return vector;
}

void vec2Add(vec2* a, vec2* b) {
    a->x = a->x + b->x;
    a->y = a->y + b->y;
}
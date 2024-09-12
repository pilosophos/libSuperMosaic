#include "vec2.h"

vec2 vec2Add(vec2 a, vec2 b) {
    vec2 sum = {
        x: a.x + b.x,
        y: a.y + b.y
    };
    return sum;
}
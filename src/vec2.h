#ifndef LSM_VEC2_H
#define LSM_VEC2_H

typedef struct vec2 {
    int x;
    int y;
} vec2, *vec2;

void add(vec2 *a, vec2 *b);

#endif
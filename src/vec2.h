#ifndef LSM_VEC2_H
#define LSM_VEC2_H

typedef struct vec2 {
    int x;
    int y;
} vec2;

vec2 newVec2(int x, int y);

/**
 * @brief Given A, add B to it. This is an in-place operation.
 * 
 * @param a Vector to add to
 * @param b Vector to add
 */
void vec2Add(vec2* a, vec2* b);

#endif
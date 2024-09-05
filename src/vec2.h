/**
 * @file vec2.h
 * @brief An (x,y) vector and vector functions
 */
#ifndef LSM_VEC2_H
#define LSM_VEC2_H

/**
 * @brief An (x,y) vector
 */
typedef struct vec2 {
    signed char x;
    signed char y;
} vec2;

/**
 * @brief Given A, add B to it. This is an in-place operation.
 * 
 * @param a Vector to add to
 * @param b Vector to add
 */
void vec2Add(vec2* a, vec2* b);

#endif
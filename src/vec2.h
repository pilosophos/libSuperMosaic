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
    int x;
    int y;
} vec2;

/**
 * @brief Add A to B and return the sum
 * 
 * @param a First vector
 * @param b Second vector
 * @return Vector sum
 */
vec2 vec2Add(vec2 a, vec2 b);

#endif
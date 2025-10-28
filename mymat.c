#include "mymat.h"


/**
 * The function receives 3 pointers to a 2D
 * matrices (a, b and c), adds matrix b to
 * matrix a and stores the result in matrix c.
 */
void add_mat(mat* a, mat* b, mat* c) {
    int row = 0;
    int col = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            (*c)[row][col] = (*a)[row][col] + (*b)[row][col];
        }
    }
}


/**
 * The function receives 3 pointers to a 2D
 * matrices (a, b and c), subtracts matrix b
 * from matrix a and stores the result in
 * matrix c.
 */
void sub_mat(mat* a, mat* b, mat* c) {
    int row = 0;
    int col = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            (*c)[row][col] = (*a)[row][col] - (*b)[row][col];
        }
    }
}


/**
 * The function receives 3 pointers to a 2D
 * matrices (a, b and c), multiplies matrix a
 * by matrix b and stores the result of
 * multiplication in matrix c.
 */
void mul_mat(mat* a, mat* b, mat* c) {
    int row = 0;
    int col = 0;
    int rc_index = 0;
    /* initialized empty temp matrix */
    mat temp = {0};

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            /* store result in temp matrix to avoid override
               in case both pointers point to the same matrix */
            temp[row][col] = 0;
            for (rc_index = 0; rc_index < SIZE; rc_index++) {
                temp[row][col] += (*a)[row][rc_index] * (*b)[rc_index][col];
            }
        }
    }

    /* copy the multiplication result to matrix c */
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            (*c)[row][col] = temp[row][col];
        }
    }
}


/**
 * The function receives a pointer to 2D matrix a,
 * a scalar s and a pointer to another 2D matrix
 * b, multiplies matrix a by scalar s and stores
 * the result in matrix b.
 */
void mul_scalar(mat* a, double s, mat* b) {
    int row = 0;
    int col = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            (*b)[row][col] = (*a)[row][col] * s;
        }
    }
}


/**
 * The function receives 2 pointers to 2D matrices,
 * transposes the matrix a and stores the result in
 * matrix b.
 */
void trans_mat(mat* a, mat* b) {
    int row = 0;
    int col = 0;
    mat temp;

    /* store result in temp matrix to avoid override
       in case both pointers point to the same matrix */
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            temp[row][col] = (*a)[col][row];
        }
    }

    /* copy the transposed matrix to matrix b */
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            (*b)[row][col] = temp[row][col];
        }
    }
}
#ifndef __MYMAT__H__
#define __MYMAT__H__

#define SIZE 4
#define NUM_OF_MATS 6
#define NUM_OF_USED_MATS 3

typedef double mat[SIZE][SIZE];

void add_mat(mat*, mat*, mat*);
void sub_mat(mat*, mat*, mat*);
void mul_mat(mat*, mat*, mat*);
void mul_scalar(mat*, double, mat*);
void trans_mat(mat*, mat*);


#endif
/* MATLAB GENERATED SOURCE FILE: B_mat.c */
#include "B_mat.h"
uint32_t B_DATA_UINT[B_ROWS*B_COLS] = 
{
  #include "B.csv"
};
float32_t* B_DATA = (float32_t*)B_DATA_UINT;
arm_matrix_instance_f32 B;

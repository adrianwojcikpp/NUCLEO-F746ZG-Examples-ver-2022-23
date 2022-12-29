/* MATLAB GENERATED SOURCE FILE: FIR1_fir.c */
#include "FIR1_fir.h"
// Filter state
uint32_t FIR1_STATE_UINT[FIR1_NUM_TAPS+FIR1_BLOCK_SIZE-1] = {
  #include "FIR1_state_init.csv"
};
float32_t *FIR1_STATE = (float32_t*)FIR1_STATE_UINT;
// Filter coefficients
uint32_t FIR1_COEFFS_UINT[FIR1_NUM_TAPS] = {
  #include "FIR1_coeffs.csv"
};
float32_t *FIR1_COEFFS = (float32_t*)FIR1_COEFFS_UINT;
// Filter instance
arm_fir_instance_f32 FIR1;

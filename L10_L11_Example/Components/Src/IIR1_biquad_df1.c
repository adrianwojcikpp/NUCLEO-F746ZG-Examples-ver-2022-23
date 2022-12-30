/* MATLAB GENERATED SOURCE FILE: IIR1_biquad_df1.c */
#include "IIR1_biquad_df1.h"
// Filter state
uint32_t IIR1_STATE_UINT[4*IIR1_NUM_STAGES] = {
  #include "IIR1_state_init.csv"
};
float32_t *IIR1_STATE = (float32_t*)IIR1_STATE_UINT;
// Filter coefficients
uint32_t IIR1_COEFFS_UINT[5*IIR1_NUM_STAGES] = {
  #include "IIR1_coeffs.csv"
};
float32_t *IIR1_COEFFS = (float32_t*)IIR1_COEFFS_UINT;
// Filter instance
arm_biquad_casd_df1_inst_f32 IIR1;

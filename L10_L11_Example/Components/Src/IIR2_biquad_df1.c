/* MATLAB GENERATED SOURCE FILE: IIR2_biquad_df1.c */
#include "IIR2_biquad_df1.h"
// Filter state
uint32_t IIR2_STATE_UINT[4*IIR2_NUM_STAGES] = {
  #include "IIR2_state_init.csv"
};
float32_t *IIR2_STATE = (float32_t*)IIR2_STATE_UINT;
// Filter coefficients
uint32_t IIR2_COEFFS_UINT[5*IIR2_NUM_STAGES] = {
  #include "IIR2_coeffs.csv"
};
float32_t *IIR2_COEFFS = (float32_t*)IIR2_COEFFS_UINT;
// Filter instance
arm_biquad_casd_df1_inst_f32 IIR2;

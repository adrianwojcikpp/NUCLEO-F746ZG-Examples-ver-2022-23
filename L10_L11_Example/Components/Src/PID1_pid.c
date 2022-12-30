/* MATLAB GENERATED SOURCE FILE: PID1_pid.c */
#include "PID1_pid.h"
// Controller gains
uint32_t PID1_GAINS_UINT[3] = 
{
  #include "PID1_gains.csv"
};
// Controller instance
arm_pid_instance_f32 PID1;

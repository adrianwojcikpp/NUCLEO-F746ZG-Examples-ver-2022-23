/* MATLAB GENERATED  HEADER FILE: PID1_pid.h */
#ifndef INC_PID1_H_
#define INC_PID1_H_

#include "arm_math.h"

// Controller gains
extern uint32_t PID1_GAINS_UINT[3];
#define PID1_KP  (((float32_t*)PID1_GAINS_UINT)[0])
#define PID1_KI  (((float32_t*)PID1_GAINS_UINT)[1])
#define PID1_KD  (((float32_t*)PID1_GAINS_UINT)[2])
// Controller instance
extern arm_pid_instance_f32 PID1;
#endif // INC_PID1_H_

/**
  ******************************************************************************
  * @file     : pid2dof_config.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 06 Sep, 2021
  * @brief    : Simple PID controller implementation.
  *             Configuration file.
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include <pid2dof.h>

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
PID_HandleTypeDef hlight_pid = {
  .Kp = 0.0f, .Ki = 0.5f, .Kd = 0.0f,
  .N = 0.01f, .Ts = 0.025,
	.LimitUpper = 100.0f, .LimitLower = 0.0f
};

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

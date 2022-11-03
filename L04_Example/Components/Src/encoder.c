/**
  ******************************************************************************
  * @file		: encoder.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Rotary encoder
  *
  ******************************************************************************
  */
  
/* Includes ------------------------------------------------------------------*/
#include "encoder.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

#ifdef ENC_HARDWARE_COUNTER

/**
 * @brief Rotary quadrature encoder hardware initialization.
 * @param[in] hbtn Encoder handler
 * @return None
 */
void ENC_Init(ENC_HandleTypeDef* henc)
{
  // TODO
}

/**
 * @brief Rotary quadrature encoder hardware counter read.
 * @param[in] hbtn Encoder handler
 * @return Current counter value
 */
uint32_t ENC_GetCounter(ENC_HandleTypeDef* henc)
{
  // TODO
}

#else

/**
 * @brief Rotary quadrature encoder software counter update procedure.
 * @param[in] hbtn Encoder handler
 * @return Current counter value
 */
int32_t ENC_UpdateCounter(ENC_HandleTypeDef* henc)
{
  GPIO_PinState dt = HAL_GPIO_ReadPin(henc->DT_Port, henc->DT_Pin);
  int32_t cnt = henc->Counter;
  if(dt == GPIO_PIN_RESET)
    henc->Counter = (henc->Counter >= henc->CounterMax) ? henc->CounterMax : (henc->Counter + henc->CounterStep);
  else
    henc->Counter = (henc->Counter <= henc->CounterMin) ? henc->CounterMin : (henc->Counter - henc->CounterStep);
  henc->CounterInc = (henc->Counter > cnt);
  henc->CounterDec = (henc->Counter < cnt);
  return henc->Counter;
}

#endif

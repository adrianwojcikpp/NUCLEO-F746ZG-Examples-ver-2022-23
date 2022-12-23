/**
  ******************************************************************************
  * @file     : disp_config.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *             DISP_DIO - common anode display without internal driver
  *             DISP_TM1637 - display with internal TM1635 driver
  ******************************************************************************
  */
#ifndef INC_DISP_CONFIG_H_
#define INC_DISP_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "disp.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern DISP_DIO_HandleTypeDef hdisp1;
extern DISP_TM1637_HandleTypeDef hdisp2;

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_DISP_CONFIG_H_ */

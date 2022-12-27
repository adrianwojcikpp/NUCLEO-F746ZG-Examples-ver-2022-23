/**
  ******************************************************************************
  * @file		  : led_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.1
  * @date     : Nov 27, 2022
  * @brief   	: Single-color LED components configuration file
  *
  ******************************************************************************
  */
#ifndef INC_LED_CONFIG_H_
#define INC_LED_CONFIG_H_

/* Public includes -----------------------------------------------------------*/
#include "led.h"

/* Public typedef ------------------------------------------------------------*/

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
extern LED_DIO_Handle_TypeDef hldg1; //!< Green on-board LED
extern LED_DIO_Handle_TypeDef hldb1; //!< Blue on-board LED
extern LED_DIO_Handle_TypeDef hldr1; //!< Red on-board LED

extern LED_PWM_Handle_TypeDef hldg2; //!< Green breadboard THT LED
extern LED_PWM_Handle_TypeDef hldb2; //!< Blue breadboard THT LED
extern LED_PWM_Handle_TypeDef hldr2; //!< Red breadboard THT LED

extern LED_PWM_Handle_TypeDef hldg3; //!< Red channel of breadboard RGB THT LED
extern LED_PWM_Handle_TypeDef hldb3; //!< Blue channel of breadboard RGB THT LED
extern LED_PWM_Handle_TypeDef hldr3; //!< Red channel of breadboard RGB THT LED
/* Public function prototypes ------------------------------------------------*/

#endif /* INC_LED_CONFIG_H_ */

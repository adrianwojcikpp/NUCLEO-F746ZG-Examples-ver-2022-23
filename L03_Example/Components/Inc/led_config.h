/**
  ******************************************************************************
  * @file		: led_config.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
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
extern LED_GPIO_Handle_TypeDef hld1; //!< Green on-board LED
extern LED_GPIO_Handle_TypeDef hld2; //!< Blue on-board LED
extern LED_GPIO_Handle_TypeDef hld3; //!< Red on-board LED
extern LED_GPIO_Handle_TypeDef hld4; //!< Blue THT LED

/* Public function prototypes ------------------------------------------------*/

#endif /* INC_LED_CONFIG_H_ */

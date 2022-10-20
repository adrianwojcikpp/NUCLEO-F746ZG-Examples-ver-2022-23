/**
  ******************************************************************************
  * @file		: led_config.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Single-color LED components configuration file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LED_GPIO_Handle_TypeDef hld1 = LED_GPIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_GPIO_Handle_TypeDef hld2 = LED_GPIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_GPIO_Handle_TypeDef hld3 = LED_GPIO_INIT_HANDLE(LD3, LED_ON_HIGH);
LED_GPIO_Handle_TypeDef hld4 = LED_GPIO_INIT_HANDLE(LD4, LED_ON_HIGH);

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

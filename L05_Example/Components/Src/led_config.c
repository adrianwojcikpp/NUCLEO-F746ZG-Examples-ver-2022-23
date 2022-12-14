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
#include "tim.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
LED_GPIO_Handle_TypeDef hld1 = LED_GPIO_INIT_HANDLE(LD1, LED_ON_HIGH);
LED_GPIO_Handle_TypeDef hld2 = LED_GPIO_INIT_HANDLE(LD2, LED_ON_HIGH);
LED_GPIO_Handle_TypeDef hld3 = LED_GPIO_INIT_HANDLE(LD3, LED_ON_HIGH);

LED_PWM_Handle_TypeDef hld4 = { .Timer = &htim5, .Channel = TIM_CHANNEL_4 };
LED_PWM_Handle_TypeDef hldr = { .Timer = &htim2, .Channel = TIM_CHANNEL_1 };
LED_PWM_Handle_TypeDef hldg = { .Timer = &htim2, .Channel = TIM_CHANNEL_3 };
LED_PWM_Handle_TypeDef hldb = { .Timer = &htim2, .Channel = TIM_CHANNEL_4 };

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

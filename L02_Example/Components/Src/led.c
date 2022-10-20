/**
  ******************************************************************************
  * @file		: led.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Single-color LED components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "led.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
/**
  * @brief Writes to LED's GPIO pin
  * @param[in] hled		: LED GPIO handler
  * @param[in] state 	: GPIO pin state (0/1)
  * @retval None
  */
void __led_gpio_write(const LED_GPIO_Handle_TypeDef* hled, _Bool state)
{
	HAL_GPIO_WritePin(hled->Port, hled->Pin, (GPIO_PinState)state);
}

/**
  * @brief Toggles LED's GPIO pin
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void __led_gpio_toggle(const LED_GPIO_Handle_TypeDef* hled)
{
	HAL_GPIO_TogglePin(hled->Port, hled->Pin);
}

/**
  * @brief Reads LED's GPIO pin
  * @param[in] hled		: LED GPIO handler
  * @retval GPIO pin state (0/1)
  */
_Bool __led_gpio_read(const LED_GPIO_Handle_TypeDef* hled)
{
	return (_Bool)HAL_GPIO_ReadPin(hled->Port, hled->Pin);
}

#endif

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Turns LED on
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_On(const LED_GPIO_Handle_TypeDef* hled)
{
	LED_GPIO_Write(hled, LED_ON);
}

/**
  * @brief Turns LED off
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_Off(const LED_GPIO_Handle_TypeDef* hled)
{
	LED_GPIO_Write(hled, LED_OFF);
}

/**
  * @brief Toggles LED state
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_Toggle(const LED_GPIO_Handle_TypeDef* hled)
{
	__led_gpio_toggle(hled);
}

/**
  * @brief Writes given LED state
  * @param[in] hled		: LED GPIO handler
  * @param[in] state 	: LED state (LED_OFF or LED_ON)
  * @retval None
  */
void LED_GPIO_Write(const LED_GPIO_Handle_TypeDef* hled, LED_GPIO_State_TypeDef state)
{
	__led_gpio_write(hled, hled->ActiveState == LED_ON_HIGH ? state : !state);
}

/**
  * @brief Reads LED state
  * @param[in] hled		: LED GPIO handler
  * @retval	LED state (LED_OFF or LED_ON)
  */
LED_GPIO_State_TypeDef LED_GPIO_Read(const LED_GPIO_Handle_TypeDef* hled)
{
	_Bool state = __led_gpio_read(hled);
	return hled->ActiveState == LED_ON_HIGH ? state : !state;
}

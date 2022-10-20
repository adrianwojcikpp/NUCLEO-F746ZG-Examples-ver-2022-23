/**
  ******************************************************************************
  * @file		: btn.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button & switch components driver
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "btn.h"

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
  * @brief Reads button's GPIO pin
  * @param[in] hled		: button GPIO handler
  * @retval GPIO pin state (0/1)
  */
_Bool __btn_gpio_read(const BTN_GPIO_Handle_TypeDef* hbtn)
{
	return (_Bool)HAL_GPIO_ReadPin(hbtn->Port, hbtn->Pin);
}

#endif

/* Public functions ----------------------------------------------------------*/
/**
  * @brief Reads button state
  * @param[in] hbtn		: button GPIO handler
  * @retval	Button state (BTN_PRESSED or BTN_RELEASED)
  */
BTN_GPIO_State_TypeDef BTN_GPIO_Read(const BTN_GPIO_Handle_TypeDef* hbtn)
{
	_Bool state = __btn_gpio_read(hbtn);
	return (hbtn->Pull == BTN_PULL_DOWN) ? state : !state;
}

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button GPIO handler
  * @retval	1 if button is pressed, if if is released
  */
_Bool BTN_GPIO_IsPressed(const BTN_GPIO_Handle_TypeDef* hbtn)
{
	return BTN_GPIO_Read(hbtn) == BTN_PRESSED;
}

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button GPIO handler
  * @retval	1 if button is released, 0 if is pressed
  */
_Bool BTN_GPIO_IsReleased(const BTN_GPIO_Handle_TypeDef* hbtn)
{
	return BTN_GPIO_Read(hbtn) == BTN_RELEASED;
}

/**
  * @brief Detects button state change
  * @param[in/out] hbtn		: button GPIO handler
  * @retval	Detected edge (BTN_NO_EDGE, BTN_PRESSED_EDGE or BTN_RELEASED_EDGE)
  */
BTN_GPIO_Edge_TypeDef BTN_GPIO_EdgeDetected(BTN_GPIO_Handle_TypeDef* hbtn)
{
	BTN_GPIO_State_TypeDef state = BTN_GPIO_Read(hbtn);
	BTN_GPIO_Edge_TypeDef edge = BTN_NO_EDGE;
	if(state == BTN_PRESSED && hbtn->PrevState == BTN_RELEASED)
		edge = BTN_PRESSED_EDGE;
	else if(state == BTN_RELEASED && hbtn->PrevState == BTN_PRESSED)
		edge = BTN_RELEASED_EDGE;
	hbtn->PrevState = state;
	return edge;
}

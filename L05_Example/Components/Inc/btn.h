/**
  ******************************************************************************
  * @file		: btn.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Button components driver
  *
  ******************************************************************************
  */
#ifndef INC_BTN_H_
#define INC_BTN_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
/**
  * @brief GPIO (On/Off) button handle structure definition
  */
#ifdef USE_HAL_DRIVER
typedef GPIO_TypeDef* BTN_GPIO_Port_TypeDef;
typedef uint16_t BTN_GPIO_Pin_TypeDef;
#endif
typedef enum { BTN_PULL_DOWN, BTN_PULL_UP } BTN_PULL_TYPE_TypeDef;
typedef enum { BTN_RELEASED = 0, BTN_PRESSED = 1 } BTN_GPIO_State_TypeDef;
typedef enum { BTN_NO_EDGE, BTN_PRESSED_EDGE, BTN_RELEASED_EDGE } BTN_GPIO_Edge_TypeDef;

typedef struct {
	BTN_GPIO_Port_TypeDef Port;
	BTN_GPIO_Pin_TypeDef Pin;
	BTN_PULL_TYPE_TypeDef Pull;
	BTN_GPIO_State_TypeDef PrevState;
} BTN_GPIO_Handle_TypeDef;

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#define BTN_GPIO_INIT_HANDLE(USER_NAME, PULL)	\
		{ 										\
			.Port = USER_NAME##_GPIO_Port, 		\
			.Pin = USER_NAME##_Pin, 			\
			.Pull = PULL,						\
			.PrevState = BTN_RELEASED			\
		}
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
/**
  * @brief Reads button state
  * @param[in] hbtn		: button GPIO handler
  * @retval	Button state (BTN_PRESSED or BTN_RELEASED)
  */
BTN_GPIO_State_TypeDef BTN_GPIO_Read(const BTN_GPIO_Handle_TypeDef* hbtn);

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button GPIO handler
  * @retval	1 if button is pressed, if if is released
  */
_Bool BTN_GPIO_IsPressed(const BTN_GPIO_Handle_TypeDef* hbtn);

/**
  * @brief Check if button is pressed
  * @param[in] hbtn		: button GPIO handler
  * @retval	1 if button is released, 0 if is pressed
  */
_Bool BTN_GPIO_IsReleased(const BTN_GPIO_Handle_TypeDef* hbtn);

/**
  * @brief Detects button state change
  * @param[in/out] hbtn		: button GPIO handler
  * @retval	Detected edge (BTN_NO_EDGE, BTN_PRESSED_EDGE or BTN_RELEASED_EDGE)
  */
BTN_GPIO_Edge_TypeDef BTN_GPIO_EdgeDetected(BTN_GPIO_Handle_TypeDef* hbtn);

#endif /* INC_BTN_H_ */

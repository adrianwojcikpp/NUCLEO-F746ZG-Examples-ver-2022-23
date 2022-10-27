/**
  ******************************************************************************
  * @file		: led.h
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Single-color LED components driver
  *
  ******************************************************************************
  */
#ifndef INC_LED_H_
#define INC_LED_H_

/* Public includes -----------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#include "stm32f7xx_hal.h"
#endif

/* Public typedef ------------------------------------------------------------*/
/**
  * @brief GPIO (On/Off) LED handle structure definition
  */
#ifdef USE_HAL_DRIVER
typedef GPIO_TypeDef* LED_GPIO_Port_TypeDef;
typedef uint16_t LED_GPIO_Pin_TypeDef;
#endif
typedef enum { LED_ON_LOW, LED_ON_HIGH } LED_GPIO_ActiveState_TypeDef;
typedef enum { LED_OFF = 0, LED_ON = 1} LED_GPIO_State_TypeDef;

typedef struct {
	LED_GPIO_Port_TypeDef Port;
	LED_GPIO_Pin_TypeDef Pin;
	LED_GPIO_ActiveState_TypeDef ActiveState;
} LED_GPIO_Handle_TypeDef;

/**
  * @brief PWM LED handle structure definition
  */

/* Public define -------------------------------------------------------------*/

/* Public macro --------------------------------------------------------------*/
#ifdef USE_HAL_DRIVER
#define LED_GPIO_INIT_HANDLE(USER_NAME, ACTIVE_STATE)	\
		{ 												\
			.Port = USER_NAME##_GPIO_Port, 				\
			.Pin = USER_NAME##_Pin, 					\
			.ActiveState = ACTIVE_STATE					\
		}
#endif

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/**
  * @brief Turns LED on
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_On(const LED_GPIO_Handle_TypeDef* hled);

/**
  * @brief Turns LED off
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_Off(const LED_GPIO_Handle_TypeDef* hled);

/**
  * @brief Toggles LED state
  * @param[in] hled		: LED GPIO handler
  * @retval None
  */
void LED_GPIO_Toggle(const LED_GPIO_Handle_TypeDef* hled);

/**
  * @brief Writes given LED state
  * @param[in] hled		: LED GPIO handler
  * @param[in] state 	: LED state (LED_OFF or LED_ON)
  * @retval None
  */
void LED_GPIO_Write(const LED_GPIO_Handle_TypeDef* hled, LED_GPIO_State_TypeDef state);

/**
  * @brief Reads LED state
  * @param[in] hled		: LED GPIO handler
  * @retval	LED state (LED_OFF or LED_ON)
  */
LED_GPIO_State_TypeDef LED_GPIO_Read(const LED_GPIO_Handle_TypeDef* hled);

#endif /* INC_LED_H_ */

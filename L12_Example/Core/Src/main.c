/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dac.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "led_config.h"
#include "btn_config.h"
#include "encoder_config.h"
#include "bh1750_config.h"
#include "bmp2_config.h"
#include "aio.h"
#include "arm_math.h"
#include "disp_config.h"
#include "lcd_config.h"
#include "menu_config.h"
extern unsigned int ADC1_ConvResults_mV[16];
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FIR_NUM_TAPS (sizeof(fir_coeffs)/sizeof(float32_t))
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t RxData[8];
const uint16_t RX_DATA_LEN = 3;
uint16_t ADC1_DATA[16];
arm_fir_instance_f32 fir[2];
const uint32_t fir_coeffs[] = {
  #include "fir_coeffs.csv"
};
float32_t fir_state[2][64];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim == htim_disp)
  {
    DISP_DIO_ROUTINE(&hdisp1);
  }
  else if(htim == hmenu.Timer)
  {
    if(BTN_DIO_EdgeDetected(&hbtn2) == BTN_PRESSED_EDGE && hmenu.Item->Next != NULL)
    {
      hmenu.Item = hmenu.Item->Next;
      hmenu.ItemChanged = 1;
    }

    if(BTN_DIO_EdgeDetected(&hbtn1) == BTN_PRESSED_EDGE && hmenu.Item->Prev != NULL)
    {
      hmenu.Item = hmenu.Item->Prev;
      hmenu.ItemChanged = 1;
    }

    MENU_ROUTINE(&hmenu);

    DISP_DIO_printDecUInt(&hdisp1, ADC1_ConvResults_mV[0]);
    DISP_TM1637_printDecUInt(&hdisp2, ADC1_ConvResults_mV[1]);
  }
  else if(htim == htim_inputs)
  {
    static int time_ms = 0;

    HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADC1_DATA, hadc1.Init.NbrOfConversion);

    if(time_ms % 200 == 0)
      BH1750_ReadIlluminance_lux(&hbh1750_1);

    if(time_ms % 250 == 0)
      BMP2_ReadTemperature_degC(&bmp2dev_1);

    time_ms += 50;
    if(time_ms == 1000)
      time_ms = 0;
  }
}

/**
  * @brief  Regular conversion complete callback in non blocking mode
  * @param  hadc pointer to a ADC_HandleTypeDef structure that contains
  *         the configuration information for the specified ADC.
  * @retval None
  */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
  if(hadc == &hadc1)
  {
    for(int i = 0; i < hadc1.Init.NbrOfConversion; i++)
    {
      float in_tmp = ADC_REG2VOLTAGE(ADC1_DATA[i]);
      float out_tmp;
      arm_fir_f32(&fir[i], &in_tmp, &out_tmp, 1);
      if(abs(ADC1_ConvResults_mV[i] - (uint16_t)out_tmp) > 10)
        ADC1_ConvResults_mV[i] = out_tmp;
    }
  }
}

/**
  * @brief  Rx Transfer completed callback.
  * @param  huart UART handle.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart == hmenu.SerialPort)
  {
	 int dac_value;
	 int n = sscanf((uint8_t*)RxData, "%x", &dac_value);
	 if(n == 1)
		 HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
	 HAL_UART_Receive_IT(hmenu.SerialPort, RxData, RX_DATA_LEN);
  }
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_I2C1_Init();
  MX_TIM7_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_SPI4_Init();
  MX_ADC1_Init();
  MX_DAC_Init();
  /* USER CODE BEGIN 2 */
  arm_fir_init_f32(&fir[0], FIR_NUM_TAPS, (const float32_t*)fir_coeffs, fir_state[0], 1);
  arm_fir_init_f32(&fir[1], FIR_NUM_TAPS, (const float32_t*)fir_coeffs, fir_state[1], 1);

  BH1750_Init(&hbh1750_1);
  BMP2_Init(&bmp2dev_1);

  LED_PWM_Init(&hldr2);
  LED_PWM_Init(&hldg2);
  LED_PWM_Init(&hldb2);
  LED_PWM_Init(&hldr3);
  LED_PWM_Init(&hldg3);
  LED_PWM_Init(&hldb3);

  ENC_Init(&henc1);

  LCD_DIO_Init(&hlcd1);
  DISP_TM1637_Init(&hdisp2);

  MENU_Init(&hmenu);

  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);

  HAL_TIM_Base_Start_IT(htim_disp);
  HAL_TIM_Base_Start_IT(htim_inputs);
  HAL_TIM_Base_Start_IT(hmenu.Timer);

  HAL_UART_Receive_IT(hmenu.SerialPort, RxData, RX_DATA_LEN);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    // Empty loop
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  ******************************************************************************
  * @file     : disp_config.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *             DISP_DIO - common anode display without internal driver
  *             DISP_TM1637 - display with internal TM1635 driver
  ******************************************************************************
  */
/* Private includes ----------------------------------------------------------*/
#include "disp.h"
#include "main.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
DISP_DIO_HandleTypeDef hdisp1 = {
  // Display GPIO ports and pins
  .SegmentOutput = {
      DIO_INIT_HANDLE(DISP_A),
      DIO_INIT_HANDLE(DISP_B),
      DIO_INIT_HANDLE(DISP_C),
      DIO_INIT_HANDLE(DISP_D),
      DIO_INIT_HANDLE(DISP_E),
      DIO_INIT_HANDLE(DISP_F),
      DIO_INIT_HANDLE(DISP_G)
  },
  .DigitOutput = {
      DIO_INIT_HANDLE(DISP_1),
      DIO_INIT_HANDLE(DISP_2),
      DIO_INIT_HANDLE(DISP_3),
      DIO_INIT_HANDLE(DISP_4)
  },
  .DecimalPointOutput = DIO_INIT_HANDLE(DISP_H),
  // Display data
  .DataArray = {0, 0, 0, 0},
  .DecimalPoint = DISP_NONE
};

DISP_TM1637_HandleTypeDef hdisp2 = {
  .CLK = DIO_INIT_HANDLE(DISP_CLK),
  .DIO = DIO_INIT_HANDLE(DISP_DIO),
  .Separator = TM1637_SEP_NONE
};

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  ******************************************************************************
  * @file     : disp.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *
  ******************************************************************************
  */
  
/* Private includes ----------------------------------------------------------*/
#include "disp.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define DISP_EMPTY_CHAR   10
#define DISP_DECIMALS_NO  10

/* Private macro -------------------------------------------------------------*/
#define __POWER_OF_TEN(n) 1e##n

/* Private variables ---------------------------------------------------------*/
const uint8_t DISP_COMMON_ANODE_DECIMALS[] = {
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90, 0xFF
};

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
void disp_write_data(DISP_HandleTypeDef* hdisp, uint8_t data)
{
  for(uint8_t i = 0; i < DISP_SEG_NO; i++)
    DIO_Write(&(hdisp->SegmentOutput[i]), (data >> i) & 0x01);
}

void disp_disable_all_digits(DISP_HandleTypeDef* hdisp)
{
  for(uint8_t i = 0; i < DISP_DIG_NO; i++)
    DIO_WriteLow(&(hdisp->DigitOutput[i]));
}

void disp_enable_digit(DISP_HandleTypeDef* hdisp, uint8_t dig)
{
  if(dig < DISP_DIG_NO)
    DIO_WriteHigh(&(hdisp->DigitOutput[dig]));
}

void disp_enable_decimal_point(DISP_HandleTypeDef* hdisp)
{
  DIO_WriteLow(&(hdisp->DecimalPointOutput));
}

void disp_disable_decimal_point(DISP_HandleTypeDef* hdisp)
{
  DIO_WriteHigh(&(hdisp->DecimalPointOutput));
}

/* Public functions ----------------------------------------------------------*/

/**
 * @brief TODO
 * @param[in] hdisp :
 * @param[in] dp    :
 */
void DISP_EnableDecimalPoint(DISP_HandleTypeDef* hdisp, DISP_DP_TypeDef dp)
{
  hdisp->DecimalPoint = dp;
}

/**
 * @brief TODO
 * @param[in] hdisp :
 * @param[in] dec   :
 */
void DISP_printDecUInt(DISP_HandleTypeDef* hdisp, uint16_t dec)
{
  uint16_t div = __POWER_OF_TEN(3);
  for(uint8_t i = 0; i < DISP_DIG_NO; i++)
  {
    hdisp->DataArray[i] = dec / div;
    dec = dec % div;
    div /= 10;
  }
}

/**
 * @brief TODO
 * @param[in] hdisp :
 */
void DISP_ROUTINE(DISP_HandleTypeDef* hdisp)
{
  static uint8_t dig = 0;  // active digit selector

  // Disable all segments
  disp_disable_all_digits(hdisp);

  // Enable single segment
  disp_enable_digit(hdisp, dig);

  // Write to selected segment
  uint8_t idx = hdisp->DataArray[dig];
  
  /* DECIMAL POSITIVE NUMBERS: 0000-9999 */
  if(idx < DISP_DECIMALS_NO)
    disp_write_data(hdisp, DISP_COMMON_ANODE_DECIMALS[idx]);
  
  //else if(...) 
  /* text handling, 
     hex number handling, 
     negative decimal number handling 
     etc */
     
  /* EMPTY CHARACTER (BLANK) */
  else
    disp_write_data(hdisp, DISP_COMMON_ANODE_DECIMALS[DISP_EMPTY_CHAR]);

  // Decimal point control
  if(hdisp->DecimalPoint == dig)
    disp_enable_decimal_point(hdisp);
  else
    disp_disable_decimal_point(hdisp);

  // Select next segment
  dig = (dig < DISP_DIG_NO-1) ? (dig+1) : (0);
}

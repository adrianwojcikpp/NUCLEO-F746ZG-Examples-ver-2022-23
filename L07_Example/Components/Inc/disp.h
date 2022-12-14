/**
  ******************************************************************************
  * @file     : disp.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.2.0
  * @date     : 4-Nov-2020
  * @brief    : Simple 4 x 8 segment LED display driver library.
  *
  ******************************************************************************
  */
#ifndef INC_DISP_H_
#define INC_DISP_H_

/* Public includes -----------------------------------------------------------*/
#include <stdint.h>
#include "dio.h"

/* Public define -------------------------------------------------------------*/
#define DISP_SEG_NO 7  //!< Without decimal point segment
#define DISP_DIG_NO 4

/* Public typedef ------------------------------------------------------------*/
typedef enum {
  DISP_DP_1 = 0, DISP_DP_2, DISP_DP_3, DISP_DP_4, DISP_NONE
} DISP_DP_TypeDef;

typedef struct {
  // Display GPIO ports and pins
  DIO_Handle_TypeDef DigitOutput[DISP_DIG_NO];
  DIO_Handle_TypeDef SegmentOutput[DISP_SEG_NO];
  DIO_Handle_TypeDef DecimalPointOutput;
  // Display data
  uint8_t DataArray[DISP_DIG_NO];
  DISP_DP_TypeDef  DecimalPoint;
} DISP_HandleTypeDef;

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void DISP_EnableDecimalPoint(DISP_HandleTypeDef* hdisp, DISP_DP_TypeDef dp);
void DISP_printDecUInt(DISP_HandleTypeDef* hdisp, uint16_t dec);
void DISP_ROUTINE(DISP_HandleTypeDef* hdisp);

#endif /* INC_DISP_H_ */

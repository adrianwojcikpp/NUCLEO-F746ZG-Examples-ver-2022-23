/**
  ******************************************************************************
  * @file     : menu_config.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : 12-Jan-2021
  * @brief    : Simple linked-list menu example.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"
#include <stdio.h>

#include "usart.h"
#include "tim.h"
#include "dac.h"

#include "aio.h"
#include "lcd_config.h"
#include "led_config.h"
#include "encoder_config.h"
#include "bh1750_config.h"
#include "bmp2_config.h"

/* Private function prototypes -----------------------------------------------*/
void menu_dout_routine(MenuItem_TypeDef* hmenuitem, DIO_Handle_TypeDef* hdio, const char* name);
void menu_pwm_routine(MenuItem_TypeDef* hmenuitem, PWM_Handle_TypeDef* hpwm, const char* name);
void menu_uint_io_routine(MenuItem_TypeDef* hmenuitem, unsigned int value, unsigned int len, const char* name, const char* unit);
void menu_float_io_routine(MenuItem_TypeDef* hmenuitem, float value, unsigned int len, const char* name, const char* unit);
void menu_dac_routine(MenuItem_TypeDef* hmenuitem, uint32_t channel, const char* name);

/* Public variables ----------------------------------------------------------*/
Menu_TypeDef hmenu = {
  .Display = &hlcd1, .Timer = &htim11, .SerialPort = &huart3,
};

unsigned int ADC1_ConvResults_mV[16];

/* Private variables ---------------------------------------------------------*/

MENU_ITEM_CONTRUCTOR(menu_ldr1, { menu_dout_routine(hmenuitem, &(hldr1.Output), "LDR1"); } );
MENU_ITEM_CONTRUCTOR(menu_ldg1, { menu_dout_routine(hmenuitem, &(hldg1.Output), "LDG1"); } );
MENU_ITEM_CONTRUCTOR(menu_ldb1, { menu_dout_routine(hmenuitem, &(hldb1.Output), "LDB1"); } );

MENU_ITEM_CONTRUCTOR(menu_ldr2, { menu_pwm_routine(hmenuitem, &(hldr2.Output), "LDR2"); } );
MENU_ITEM_CONTRUCTOR(menu_ldg2, { menu_pwm_routine(hmenuitem, &(hldg2.Output), "LDG2"); } );
MENU_ITEM_CONTRUCTOR(menu_ldb2, { menu_pwm_routine(hmenuitem, &(hldb2.Output), "LDB2"); } );

MENU_ITEM_CONTRUCTOR(menu_ldrgb_r, { menu_pwm_routine(hmenuitem, &(hldr3.Output), "LD [R]GB"); } );
MENU_ITEM_CONTRUCTOR(menu_ldrgb_g, { menu_pwm_routine(hmenuitem, &(hldg3.Output), "LD R[G]B"); } );
MENU_ITEM_CONTRUCTOR(menu_ldrgb_b, { menu_pwm_routine(hmenuitem, &(hldb3.Output), "LD RG[B]"); } );

MENU_ITEM_CONTRUCTOR(menu_enc1, { menu_uint_io_routine(hmenuitem, ENC_GetCounter(&henc1), 3, "ENC", ""); } );

MENU_ITEM_CONTRUCTOR(menu_ain1, { menu_uint_io_routine(hmenuitem, ADC1_ConvResults_mV[0], 4, "POT1", "mV"); } );
MENU_ITEM_CONTRUCTOR(menu_ain2, { menu_uint_io_routine(hmenuitem, ADC1_ConvResults_mV[1], 4, "POT2", "mV"); } );

MENU_ITEM_CONTRUCTOR(menu_bmp2,   { menu_float_io_routine(hmenuitem, BMP2_GET_TEMP(&bmp2dev_1), 5, "TEMP", "degC"); } );
MENU_ITEM_CONTRUCTOR(menu_bh1750, { menu_float_io_routine(hmenuitem, hbh1750_1.Readout, 6, "LIGHT", "lx"); } );

MENU_ITEM_CONTRUCTOR(menu_aout1, { menu_dac_routine(hmenuitem, DAC_CHANNEL_1, "DAC CH1"); } );

#define MENU_MAIN_LEN (sizeof(MENU_MAIN_ARRAY)/sizeof(MENU_MAIN_ARRAY[0]))
MenuItem_TypeDef* MENU_MAIN_ARRAY[] = { /* Main menu list */
  &menu_ldr1,     /* LED Red #1: on-board red LED (LD3) */
  &menu_ldr2,     /* LED Red #2: breadboard red LED (LD6 */
  &menu_ldg1,     /* LED Green #1: on-board green LED (LD1) */
  &menu_ldg2,     /* LED Green #2: breadboard green LED (LD4) */
  &menu_ldb1,     /* LED Blue #1: on-board blue LED (LD2) */
  &menu_ldb2,     /* LED Blue #2: breadboard blue LED (LD5) */
  &menu_ldrgb_r,  /* LED RGB: channel R */
  &menu_ldrgb_g,  /* LED RGB: channel G */
  &menu_ldrgb_b,  /* LED RGB: channel B */
  &menu_enc1,     /* Rotary encoder #1 */
  &menu_ain1,     /* Analog input #1 */
  &menu_ain2,     /* Analog input #2 */
  &menu_bmp2,     /* Temperature & pressure sensor: BMP280 */
  &menu_bh1750,   /* Light sensor: BH1750 */
  &menu_aout1     /* Analog output #1 */
};

/* Private function ----------------------------------------------------------*/

/**
 * @brief Common digital output menu routine.
 * @param[in/out] hmenuitem : Menu item structure
 * @param[in]     hled      : Digital output handler
 * @param[in]     name      : Output display name
 */
void menu_dout_routine(MenuItem_TypeDef* hmenuitem, DIO_Handle_TypeDef* hdio, const char* name)
{
  if(hmenu.Item == hmenuitem) // If active component
  {
    ENC_GetCounter(&henc1);
    if(henc1.CounterInc)
      DIO_WriteHigh(hdio);
    else if(henc1.CounterDec)
      DIO_WriteLow(hdio);
  }

  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %s", name, DIO_Read(hdio) ? "ON" : "OFF");
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

/**
 * @brief Common PWM menu routine.
 * @param[in/out] hmenuitem : Menu item structure
 * @param[in]     hpwm      : PWM output handler
 * @param[in]     name      : Output display name
 */
void menu_pwm_routine(MenuItem_TypeDef* hmenuitem, PWM_Handle_TypeDef* hpwm, const char* name)
{
  if(hmenu.Item == hmenuitem) // If active component
  {
    if(hmenu.ItemChanged) // Reload counter if item changed
      ENC_SetCounter(&henc1, PWM_ReadDuty(hpwm));
    PWM_WriteDuty(hpwm, ENC_GetCounter(&henc1));
  }

  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %3d%%", name, (int)PWM_ReadDuty(hpwm));
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

void menu_uint_io_routine(MenuItem_TypeDef* hmenuitem, unsigned int value, unsigned int len, const char* name, const char* unit)
{
  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %*d %s", name, len, value, unit);
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

void menu_float_io_routine(MenuItem_TypeDef* hmenuitem, float value, unsigned int len, const char* name, const char* unit)
{
  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %*.2f%s", name, len, value, unit);
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

void menu_dac_routine(MenuItem_TypeDef* hmenuitem, uint32_t channel, const char* name)
{
  if(hmenu.Item == hmenuitem) // If active component
  {
    if(hmenu.ItemChanged) // Reload counter if item changed
      ENC_SetCounter(&henc1, DAC_REG2PERCENT(HAL_DAC_GetValue(&hdac, channel)));
    HAL_DAC_SetValue(&hdac, channel, DAC_ALIGN_12B_R, DAC_PERCENT2REG(ENC_GetCounter(&henc1)));
  }
  char temp_str[LCD_LINE_BUF_LEN];
  hmenuitem->DisplayStrLen = snprintf(temp_str, LCD_LINE_LEN, "%s: %4dmV", name, (int)DAC_REG2VOLTAGE(HAL_DAC_GetValue(&hdac, channel)));
  MENU_ITEM_WriteDisplayBuffer(hmenuitem, temp_str); // Set display buffer
  hmenuitem->SerialPortStrLen = 0;
}

/* Public function -----------------------------------------------------------*/
/**
 * @brief Menu initialization. Creates doubly-linked list from elements of MENU_MAIN_ARRAY.
 * @param[in/out] hmenu : Menu structure
 */
void MENU_Init(Menu_TypeDef* hmenu)
{
  /* Active element initialization */
  hmenu->Item = MENU_MAIN_ARRAY[0];

  /* Main menu initialization */
  for(uint8_t i = 0; i < (uint8_t)(MENU_MAIN_LEN-1); i++) //< Next item
    MENU_MAIN_ARRAY[i]->Next = MENU_MAIN_ARRAY[i+1];
  for(uint8_t i = 1; i < (uint8_t)MENU_MAIN_LEN; i++)     //< Previous item
    MENU_MAIN_ARRAY[i]->Prev = MENU_MAIN_ARRAY[i-1];
  /* Cyclic list */
  MENU_MAIN_ARRAY[MENU_MAIN_LEN-1]->Next = MENU_MAIN_ARRAY[0]; //< Next of last is first item
  MENU_MAIN_ARRAY[0]->Prev = MENU_MAIN_ARRAY[MENU_MAIN_LEN-1]; //< Previous of first is last item

  /* LCD set-up */
  LCD_DIO_SetCursor(hmenu->Display, 0, 0);
  LCD_DIO_printf(hmenu->Display, "%c", LCD_MENU_CURSOR_CHAR);
  LCD_DIO_SetCursor(hmenu->Display, 1, 0);
  LCD_DIO_printStr(hmenu->Display, " ");
}

/**
 * @brief Menu routine. Calls active items routines and updates output devices.
 * @param[in/out] hmenu : Menu structure
 */
void MENU_ROUTINE(Menu_TypeDef* hmenu)
{
  MENU_CALL_ROUTINE(hmenu->Item);
  MENU_CALL_ROUTINE(hmenu->Item->Next);

  hmenu->ItemChanged = 0;

  // #1 line - active item
  LCD_DIO_SetCursor(hmenu->Display, 0, 1);
  LCD_DIO_printStr(hmenu->Display, hmenu->Item->DisplayStr);

  // #1 line - next item
  LCD_DIO_SetCursor(hmenu->Display, 1, 1);
  LCD_DIO_printStr(hmenu->Display, hmenu->Item->Next->DisplayStr);

  // Serial port streaming
  HAL_UART_Transmit(hmenu->SerialPort, (uint8_t*)hmenu->Item->SerialPortStr, hmenu->Item->SerialPortStrLen, 10);
}


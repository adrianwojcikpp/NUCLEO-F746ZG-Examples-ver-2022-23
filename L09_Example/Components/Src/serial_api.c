/**
  ******************************************************************************
  * @file     : serial_api.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Dec 10, 2022
  * @brief    : Light control system serial port API
  *             Source file
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include "serial_api.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
_Bool Serial_API_IsCmdSet(Serial_API_Buffer* RxBuffer)
{
  return strncmp(RxBuffer->CmdStr.cmd, "SET", CMD_SIZE) == 0;
}

_Bool Serial_API_IsCmdGet(Serial_API_Buffer* RxBuffer)
{
  return strncmp(RxBuffer->CmdStr.cmd, "GET", CMD_SIZE) == 0;
}

void Serial_API_GetSysVar(Serial_API_Buffer* RxBuffer, SysVars_TypeDef* SysVars, unsigned int SysVarLen, uint64_t TimeMs)
{
  for(unsigned int i = 0; i < SysVarLen; i++)
  {
    if(strncmp(RxBuffer->CmdStr.var_id, SysVars[i].var_id, VAR_ID_SIZE) == 0)
    {
      uint8_t TxResponse[256];
      static const char TxJsonFormat[] = "{\"time\":%d,\"name\":\"%s\",\"value\":%10.3f,\"unit\":%s}\n";
      int TXRESPONSE_SIZE = sprintf((char*)TxResponse, TxJsonFormat, (int)TimeMs, SysVars[i].var_name, *(SysVars[i].val), SysVars[i].var_unit);
      HAL_UART_Transmit(CONTROL_UART, TxResponse, TXRESPONSE_SIZE, 100);
	  break;
    }
  }
}

void Serial_API_SetSysVar(Serial_API_Buffer* RxBuffer, SysVars_TypeDef* SysVars, unsigned int SysVarLen)
{
  for(unsigned int i = 0; i < SysVarLen; i++)
  {
    if(strncmp(RxBuffer->CmdStr.var_id, SysVars[i].var_id, VAR_ID_SIZE) == 0)
    {
      sscanf(RxBuffer->CmdStr.val, "%6f", SysVars[i].val);
	  break;
    }
  }
}



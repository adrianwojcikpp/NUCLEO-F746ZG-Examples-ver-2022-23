/**
  ******************************************************************************
  * @file     : serial_api.h
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : Dec 10, 2022
  * @brief    : Light control system serial port API
  *             Header file.
  *
  ******************************************************************************
  */

#ifndef INC_SERIAL_API_H_
#define INC_SERIAL_API_H_

/* Public includes -----------------------------------------------------------*/
#include <stdint.h>

/* Public define -------------------------------------------------------------*/

//<!
#define CMD_SIZE 3u

//<!
#define VAR_ID_SIZE 3u

/* Public typedef ------------------------------------------------------------*/

/**
 * TODO
 */
typedef struct {
  char cmd[CMD_SIZE];
  char colon_1;
  char var_id[VAR_ID_SIZE];
  char colon_2;
  char val[6];
} Serial_API_CmdStr;

/**
 * TODO
 */
typedef union {
  Serial_API_CmdStr CmdStr;
  uint8_t Buffer[sizeof(Serial_API_CmdStr)];
} Serial_API_Buffer;

/**
 * TODO
 */
typedef struct {
  float* val;
  const char var_id[VAR_ID_SIZE];
  const char var_name[32];
  const char var_unit[8];
} SysVars_TypeDef;

/* Public macro --------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
_Bool Serial_API_IsCmdSet(Serial_API_Buffer* RxBuffer);
_Bool Serial_API_IsCmdGet(Serial_API_Buffer* RxBuffer);
void Serial_API_GetSysVar(Serial_API_Buffer* RxBuffer, SysVars_TypeDef* SysVars, unsigned int SysVarLen, uint64_t TimeMs);
void Serial_API_SetSysVar(Serial_API_Buffer* RxBuffer, SysVars_TypeDef* SysVars, unsigned int SysVarLen);

#endif /* INC_SERIAL_API_H_ */

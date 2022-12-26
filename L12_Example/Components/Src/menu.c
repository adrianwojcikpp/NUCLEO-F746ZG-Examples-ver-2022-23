/**
  ******************************************************************************
  * @file     : menu.c
  * @author   : AW    Adrian.Wojcik@put.poznan.pl
  * @version  : 1.3.0
  * @date     : 12-Jan-2021
  * @brief    : Simple linked-list menu example.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "menu.h"

/* Typedef -------------------------------------------------------------------*/

/* Define --------------------------------------------------------------------*/

/* Macro ---------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
  const char __menu__padding[] = "                    "; // space x20
/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private function ----------------------------------------------------------*/

/* Public function -----------------------------------------------------------*/

/**
 * @brief Clear menu item display buffer content (write spaces)
 * @param[out] hmenuitem : Menu item handler
 */
void MENU_ITEM_ClearDisplayBuffer(MenuItem_TypeDef* hmenuitem)
{
  sprintf(hmenuitem->DisplayStr, "%.*s", LCD_LINE_LEN, __menu__padding);
}

/**
 * @brief Write menu item display buffer content
 * @param[in/out] hmenuitem : Menu item handler
 */
void MENU_ITEM_WriteDisplayBuffer(MenuItem_TypeDef* hmenuitem, const char* str)
{
  int pad_len = LCD_LINE_LEN - hmenuitem->DisplayStrLen;
  sprintf(hmenuitem->DisplayStr, "%s%.*s", str, pad_len, __menu__padding);
}

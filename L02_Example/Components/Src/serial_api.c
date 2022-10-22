/**
  ******************************************************************************
  * @file		: serial_api.c
  * @author  	: AW		Adrian.Wojcik@put.poznan.pl
  * @version 	: 1.3.0
  * @date    	: Oct 19, 2022
  * @brief   	: Serial API: simple output control and input readout
  *
  ******************************************************************************
  */

/* Private includes ----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "serial_api.h"
#ifdef SERIAL_API_JSON
#include "jsmn.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define LED_CTRL_OBJ_SIZE 2 //<! { "id":"LDx","state":X}

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
jsmn_parser JSMN_PARSER;
jsmntok_t JSMN_TOK[64];

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/
/**
 * @brief Comparison of a JSMN_STRING token to a C-string
 * @param[in] json : JSON C-string (token data source)
 * @param[in] tok  : JSMN token for comparison
 * @param[in] str  : C-string for comparison
 * @retval 1 if token content is the same as string, 0 otherwise
 */
_Bool __jsmn_tok_str_cmp(const char *json, jsmntok_t *tok, const char *str)
{
	_Bool is_string = (tok->type == JSMN_STRING);
	_Bool is_len_eq = ((int)strlen(str) == tok->end - tok->start);
	_Bool is_str_eq = (strncmp(json + tok->start, str, tok->end - tok->start) == 0);
	return is_string && is_len_eq && is_str_eq;
}

/**
 * @brief Comparison of a C-string key and value JSMN type with JSMN tokens
 * @param[in] json : JSON C-string (token data source)
 * @param[in] tok  : JSMN token for comparison
 * @param[in] str  : C-string for key comparison
 * @param[in] type : JSMN token type for value type comparison
 * @retval 1 if token is contains given key and next tokens have given JSMN type, <0 otherwise
 */
_Bool __jsmn_tok_keyvalue_cmp(const char *json, jsmntok_t *tok, const char *str, jsmntype_t type)
{
	_Bool is_key_eq = __jsmn_tok_str_cmp(json, tok, str);
	_Bool is_value_type_eq = ((tok+1)->type == type);
	return is_key_eq && is_value_type_eq;
}

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Serial API LED control message reading
 * @note Control message syntax: [{"id":"LDx","status":x}, ... ,{"id":"LDx","status":x}]
 * 		 where x is either 0 (LED off) or 1 (LED on)
 * 		 LEDs IDs: Green on-board LED       : LD1
 * 		           Blue on-board LED        : LD2
 * 		           Red on-board LED         : LD3
 * 		           Blue THT bread-board LED : LD4
 *
 * @param[in] 	  msg		: Input message
 * @param[in/out] leds		: Serial API LED control structure array
 * @param[in] 	  leds_len	: Serial API LED control structure array's length
 * @retval Parsing status: 0 if successful, <0 otherwise
 */
int SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int leds_len)
{
	jsmn_init(&JSMN_PARSER);
	int r = jsmn_parse(&JSMN_PARSER, msg, strlen(msg), JSMN_TOK, sizeof(JSMN_TOK) / sizeof(JSMN_TOK[0]));

	if(r < 6)
	{
		puts("Incorrect message syntax [1: Too few JSON tokens].\r\n");
		return -1;
	}

	if(JSMN_TOK[0].type != JSMN_ARRAY)
	{
		puts("Incorrect message syntax [2: An array was expected].\r\n");
		return -2;
	}
	const int len = JSMN_TOK[0].size;
	int i = 1;
	for(int n = 0; n < len; n++)
	{
		// { "key" : "value" } pairs plus 'object' token overhead
		int size = JSMN_TOK[i].size * 2 + 1;
		if(JSMN_TOK[i].type != JSMN_OBJECT)
		{
			puts("Incorrect message syntax [3: An array of objects was expected].\r\n");
			return -3;
		}
		else if(JSMN_TOK[i].size != LED_CTRL_OBJ_SIZE)
		{
			puts("Incorrect message syntax [4: Incorrect object size].\r\n");
			return -4;
		}

		int id_idx = -1, st_idx = -1;

		if(__jsmn_tok_keyvalue_cmp(msg, &JSMN_TOK[i+1], "id", JSMN_STRING)
		  && __jsmn_tok_keyvalue_cmp(msg, &JSMN_TOK[i+3], "state", JSMN_PRIMITIVE))
		{
			id_idx = i+2;
			st_idx = i+4;
		}
		else if(__jsmn_tok_keyvalue_cmp(msg, &JSMN_TOK[i+3], "id", JSMN_STRING)
		  && __jsmn_tok_keyvalue_cmp(msg, &JSMN_TOK[i+1], "state", JSMN_PRIMITIVE))
		{
			id_idx = i+4;
			st_idx = i+2;
		}
		else
		{
			puts("Incorrect message syntax [5: Can't find \"id\" or \"state\" keys].\r\n");
			return -5;
		}
		for(int k = 0; k < leds_len; k++)
		{
			if(__jsmn_tok_str_cmp(msg, &JSMN_TOK[id_idx], leds[k].Id))
				leds[k].State = strtol(msg+JSMN_TOK[st_idx].start, NULL, 10);
		}
		i = i + size;
	}

	return 0;
}

#else

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Serial API LED initialization
 */
void SERIAL_API_LED_ReadMsg(void){ }

/**
 * @brief Serial API LED control message reading
 * @param[in] 	  msg		: Input message
 * @param[in/out] leds		: Serial API LED control structure array
 * @param[in] 	  leds_len	: Serial API LED control structure array's length
 * @retval Parsing status: 0 if successful, <0 otherwise
 */
int SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int leds_len)
{
	for(int i = 0; i < leds_len; i++)
	{
		/* Message structure: 3 character ID + state as 0/1 e.g. LD11 to turn LD1 on */
		if(strncmp(leds[i].Id, msg, 3) == 0)
			leds[i].State = strtol(&msg[3], NULL, 10);
	}

	return 0;
}

#endif

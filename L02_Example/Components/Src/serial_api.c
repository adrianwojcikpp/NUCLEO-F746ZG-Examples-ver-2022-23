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
#include <string.h>
#include <stdlib.h>
#include "serial_api.h"
#include "jsmn.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define LED_CTRL_OBJ_SIZE 2

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

#ifdef SERIAL_API_JSON

/**
 * @brief TODO
 * @param[in] json :
 * @param[in] tok  :
 * @param[in] s    :
 * @retval
 */
int json_eq(const char *json, jsmntok_t *tok, const char *s)
{
	_Bool is_string = (tok->type == JSMN_STRING);
	_Bool is_len_eq = ((int)strlen(s) == tok->end - tok->start);
	_Bool is_str_eq = (strncmp(json + tok->start, s, tok->end - tok->start) == 0);

	if(is_string && is_len_eq && is_str_eq)
		return 0;

	return -1;
}

/**
 * @brief TODO
 * @param[in] json :
 * @param[in] tok  :
 * @param[in] s    :
 * @param[in] type :
 * @retval
 */
_Bool json_check_key(const char *json, jsmntok_t *tok, const char *s, jsmntype_t type)
{
	return json_eq(json, tok, s) == 0 && (tok+1)->type == type;
}


/**
 * @brief TODO
 * @param[in] type :
 * @retval
 */
char* jsmn_type2name(jsmntype_t type)
{
	switch(type)
	{
		case JSMN_OBJECT:
			return "OBJECT";
		case JSMN_ARRAY:
			return "ARRAY";
		case JSMN_STRING:
			return "STRING";
		case JSMN_PRIMITIVE:
			return "PRIMITIVE";
		default:
			return "UNDEFINED";
	}
}


/* Public functions ----------------------------------------------------------*/
/**
 * @brief TODO
 * @param[in]     msg   :
 * @param[in/out] leds  :
 * @param[in]     led_n :
 * @retval
 */
int SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int led_n)
{
	jsmn_parser p;
	jsmntok_t t[32];

	jsmn_init(&p);
	int r = jsmn_parse(&p, msg, strlen(msg), t, sizeof(t) / sizeof(t[0]));

	if(r < 6)
	{
		//puts("Incorrect message syntax [0].");
		return -1;
	}

	if(t[0].type != JSMN_ARRAY)
	{
		//puts("Incorrect message syntax [1].");
		return -2;
	}
	const int len = t[0].size;
	int i = 1;
	for(int n = 0; n < len; n++)
	{
		// { "key" : "value" } pairs plus 'object' token overhead
		int size = t[i].size * 2 + 1;
		if(t[i].type != JSMN_OBJECT)
		{
			//puts("Incorrect message syntax [2].");
			return -3;
		}
		else if(t[i].size != LED_CTRL_OBJ_SIZE)
		{
			//puts("Incorrect message syntax [3].");
			return -4;
		}

		int id_idx = -1, ps_idx = -1;

		if(json_check_key(msg, &t[i+1], "id", JSMN_STRING) && json_check_key(msg, &t[i+3], "state", JSMN_STRING))
		{
			id_idx = i+2;
			ps_idx = i+4;
		}
		else if(json_check_key(msg, &t[i+3], "id", JSMN_STRING) && json_check_key(msg, &t[i+1], "state", JSMN_STRING))
		{
			id_idx = i+4;
			ps_idx = i+2;
		}
		else
		{
			//puts("Incorrect message syntax [4].");
			return -5;
		}
		for(int k = 0; k < led_n; k++)
		{
			if(strncmp(leds[k].Id, msg+t[id_idx].start, strlen(leds[k].Id)) == 0)
				leds[k].State = strtol(msg+t[ps_idx].start, NULL, 10);
		}
		i = i + size;
	}
	return 0;
}

#else

/* Public functions ----------------------------------------------------------*/
/**
 * @brief Serial API LED control message reading
 * @param[in] 	  msg		: Input message
 * @param[in/out] leds		: Serial API LED control structure array
 * @param[in] 	  leds_n	: Serial API LED control structure array length
 */
void SERIAL_API_LED_ReadMsg(const char* msg, SERIAL_API_LED_TypeDef* leds, int leds_n)
{
	for(int i = 0; i < leds_n; i++)
	{
		/* Message structure: 3 character ID + state as 0/1 e.g. LD11 to turn LD1 on */
		if(strncmp(leds[i].Id, msg, 3) == 0)
			leds[i].State = strtol(&msg[3], NULL, 10);
	}
}


#endif

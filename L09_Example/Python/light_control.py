import serial
import math
import json

#
# @brief  
#
class SysVars_TypeDef:
	def __init__(self, time, name, value, unit):
		self.time = int(time) # ms
		self.name = name
		self.value = float(value)
		self.unit = unit
		
	def __str__(self):
		return f'{self.name}: {self.value} [{self.unit}]'
	
	def __repr__(self):
		return f'{self.name}: {self.value} [{self.unit}]'
#
# @brief  
#
class LightControl:

	# @brief TODO
	# @param[in] self     : 
	# @param[in] portname :
	# @retval 
	# 
	def __init__(self, portname):
		self.serialport = serial.Serial(portname, 115200)
		self.SETCMD = 'SET'
		self.GETCMD = 'GET'
	
	#
	# @brief TODO
	# @param[in] self   : 
	# @param[in] cmd    : 
	# @param[in] var_id :
	# @param[in] val    :
	# @retval None
	# 
	def write_cmd(self, cmd, var_id, val):
	
		if val == 0:
			val_format = '06.0f'
		else:
			val_format = f'06.{max([math.ceil(4-max([math.log10(val),0])),0])}f'
			
		self.serialport.write(bytes(f'{cmd:3}:{var_id:3}:{val:{val_format}}', encoding='utf-8'))
	
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 		
	def read_resp(self):
		resp = self.serialport.readline()
		respjson = json.loads(resp.decode("utf-8"))
		return SysVars_TypeDef(**respjson)

	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_measurement(self):
		self.write_cmd(self.GETCMD, 'RDO', 0)
		return self.read_resp()
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_control(self):
		self.write_cmd(self.GETCMD, 'PWM', 0)
		return self.read_resp()
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_reference(self):
		self.write_cmd(self.GETCMD, 'REF', 0)
		return self.read_resp()
			
	#
	# @brief TODO
	# @param[in] self  : 
	# @param[in] value :
	# @retval None
	#
	def set_reference(self, value):
		self.write_cmd(self.SETCMD, 'REF', value)
		
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @param[in] value :
	# @retval None
	# 
	def set_kp_gain(self, value):
		self.write_cmd(self.SETCMD, 'CKP', value)
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_kp_gain(self):
		self.write_cmd(self.GETCMD, 'CKP', 0)
		return self.read_resp()

	#
	# @brief TODO
	# @param[in] self  : 
	# @param[in] value :
	# @retval None
	# 
	def set_ki_gain(self, value):
		self.write_cmd(self.SETCMD, 'CKI', value)
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_ki_gain(self):
		self.write_cmd(self.GETCMD, 'CKI', 0)
		return self.read_resp()
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @param[in] value :
	# @retval None
	# 
	def set_kd_gain(self, value):
		self.write_cmd(self.SETCMD, 'CKD', value)
		
	#
	# @brief TODO
	# @param[in] self  : 
	# @retval 
	# 	
	def get_kd_gain(self):
		self.write_cmd(self.GETCMD, 'CKD', 0)
		return self.read_resp()
	
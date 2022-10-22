import json
import serial
import time

def example():
	leds = [{"id":"LD4","state":0},{"id":"LD1","state":1},{"id":"LD2","state":0},{"id":"LD3","state":0}]
	com = serial.Serial('COM8', 115200)
	msg_len = 124
	def update_leds():
		msg = json.dumps(leds).encode()
		msg = msg + b'\0'*(msg_len - len(msg))
		com.write(msg)
	
	i = 0
	while True:
		n = 0
		for led in leds:
			led["state"] = int(i == n)
			n = n +1
		i = (i + 1) % len(leds)
		update_leds()
		time.sleep(1)
		
if __name__ == "__main__":
    example()

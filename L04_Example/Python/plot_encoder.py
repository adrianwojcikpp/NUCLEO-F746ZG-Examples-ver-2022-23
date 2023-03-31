
"""
@file plot_encoder.py
@brief Python script to listen on a serial port and plot incoming data.

This script listens on a specified serial port and waits for JSON-formatted data
with a field named 'encoder'. When such a message is received, it extracts the
encoder value and plots it as a function of sample number.

Command line arguments:
    -p <port>, --port=<port>:   Serial port to listen on. Defaults to COM1.
    -b <baud>, --baud=<baud>:   Baud rate to use for serial communication.
                                Defaults to 9600.

The script uses the following Python modules:
    - serial
    - json
    - matplotlib.pyplot
    - sys
    - getopt

The script can be run as a standalone program or imported as a module.

Example usage:
    python plot_encoder.py -p COM3 -b 115200
"""

import serial
import json
import matplotlib.pyplot as plt
import sys
import getopt

if __name__ == '__main__':

    # Default values
    port = 'COM1'
    baud = 9600

    # Parse command line arguments
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'p:b:', ['port=', 'baud='])
    except getopt.GetoptError:
        print('Usage: plot_serial.py -p <port> -b <baud>')
        sys.exit(2)
    for opt, arg in opts:
        if opt in ('-p', '--port'):
            port = arg
        elif opt in ('-b', '--baud'):
            baud = int(arg)
    
    print(f'Listening on serial port {port} at {baud} baud')

    # Set up serial port
    ser = serial.Serial(port, baud)

    # Initialize plot
    fig, ax = plt.subplots()
    ax.grid(True)
    ax.set_xlabel('Sample Number')
    ax.set_ylabel('Encoder Value')
    xdata, ydata = [], []
    line, = ax.plot(xdata, ydata)

    # Main loop
    sample_num = 0
    while True:
        # Read a line from serial port
        line_str = ser.readline().decode('utf-8').rstrip('\r\n')
        
        # Parse line as JSON
        try:
            data = json.loads(line_str)
        except json.JSONDecodeError:
            continue
        
        # Check if JSON contains encoder value
        if 'encoder' in data:
            # Update plot
            encoder_val = data['encoder']
            xdata.append(sample_num)
            ydata.append(encoder_val)
            line.set_data(xdata, ydata)
            ax.relim()
            ax.autoscale_view(True,True,True)
            plt.draw()
            plt.pause(0.1)
            sample_num += 1


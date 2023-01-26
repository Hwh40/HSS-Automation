# File: Graphing.py
# Author: Henry Hall
# Date: 23/01/2022
# Description: Imports three different sets of data
# from the serial port. This plots a live graph of this data 

import numpy as np
import matplotlib.pyplot as plt
import serial
import math
import time

RUNTIME = 60


def graph_set(fig, axes):
    """Graphing settings"""
    axes.grid(True)
    axes.set_xlabel('Time (s)')
    axes.set_title('Sensor')


def main():
    """The main function"""
    fig1 = plt.figure("Figure 1")
    axes = plt.axes() 
    
    ser = serial.Serial('COM7')
    print(ser.name)
    is_done = False
    i = 1
    j = 0
    even = 0
    blank = []
    empty = []
    xs = []
    angle = []
    st = ''
    graph_set(fig1, axes)
    is_first = True
    
    while is_done != True:
        byte = (str(ser.read()))
        if is_first:
            start = time.time()
            is_first = False
        if (time.time() - start) > (RUNTIME):
            is_done = True
        if byte == "b'S'":
            even = 0
            byte = str(ser.read())
            byte = str(ser.read())
        if byte == "b'\\n'":
            if even == 0:
                blank.append(float(st))
            elif even == 1:
                empty.append(float(st))
            elif even == 2:
                angle.append(float(st))
                xs.append(time.time() - start)
                axes.cla()
                graph_set(fig1, axes)
                axes.plot(xs, blank, 'r-', label = 'Reading 1')
                axes.plot(xs, empty, 'b-', label = 'Reading 2')
                axes.plot(xs, angle, 'g-', label = 'Angle')
                axes.legend()
                plt.pause(0.001)
                j += 1
            st = ''
            even += 1
        elif byte != "b'\\n'" and byte != "b'S'" and list(byte)[2] != '\\':
            st += list(byte)[-2]
    print('Finished')
    plt.show()
    
    

main()
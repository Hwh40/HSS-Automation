import numpy as np
import matplotlib.pyplot as plt
import serial
import math

TIME = 100e-3
RUNTIME = 60


def graph_set(fig, axes, comment):
    axes.grid(True)
    axes.set_xlabel('Time (s)')
    axes.set_title('Sensor')
    axes.set_ylim([-360,360])
    axes.text(0,100, comment)
    


def main():
    comment = ''
    fig1 = plt.figure("Figure 1")
    axes = plt.axes() 
    graph_set(fig1, axes, comment)
    ser = serial.Serial('COM7')
    print(ser.name)
    is_done = False
    i = 1
    j = 0
    even = 0
    blank = []
    empty = []
    time = []
    angle = []
    st = ''
    
    while is_done != True:
        
        if j * TIME > (RUNTIME*i):
            if input('Cont: ') != '':
                is_done = True
            else:
                i+=1
        byte = (str(ser.read()))
        #print(byte)
        if byte == "b'\\n'":
            if even % 2 == 0:
                blank.append(float(st))
                st = ''
            else:
                empty.append(float(st))
                st = ''
                angle.append(180 * math.atan2(empty[-1],blank[-1]) / math.pi)
                time.append(j * TIME)
                axes.cla()
                graph_set(fig1, axes, comment)
                axes.plot(time, blank, 'r-', label = 'Reading 1')
                axes.plot(time, empty, 'b-', label = 'Reading 2')
                axes.plot(time, angle, 'g-', label = 'Angle')
                axes.legend()
                plt.pause(0.05)
                j += 1
            even += 1
        else:
            st += list(byte)[-2]
    print('Finished')
    plt.show()
    
    

main()
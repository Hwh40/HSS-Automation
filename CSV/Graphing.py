import numpy as np
import matplotlib.pyplot as plt
import serial

TIME = 100e-3
RUNTIME = 60


def graph_set(fig, axes, comment):
    axes.grid(True)
    axes.set_xlabel('Time (s)')
    axes.set_title('Sensor')
    axes.set_ylim([-110,110])
    axes.text(0,100, comment)


def main():
    comment = input('Comment:')
    fig1 = plt.figure("Figure 1")
    axes = plt.axes() 
    graph_set(fig1, axes, comment)
    ser = serial.Serial('COM7')
    print(ser.name)
    is_done = False
    i = 0
    j = 0
    blank = []
    time = []
    st = ''
    
    while is_done != True:
        if j * TIME > (RUNTIME):
            is_done = True
        byte = (str(ser.read()))
        if byte == "b'\\n'":
            try:
                blank.append(float(st))
                st = ''
                time.append(j*TIME)
                axes.cla()
                graph_set(fig1, axes, comment)
                axes.plot(time, blank, 'r-')
                plt.pause(0.05)
                j += 1
            except:
                print("Error")
                j += 1
        else:
            st += list(byte)[-2]
    
    print(blank)
    print(comment)
    plt.show()
    

main()
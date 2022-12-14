# File: Serial to CSV.py
# Author: Henry Hall
# Date: 14/12/2022
# Description: Takes serial data from a text file and
#  plots it onto a graph as well as generating a CSV. 

import numpy as np
import matplotlib.pyplot as plt

THRESHOLD = 200
INFILE = r"C:\Users\henri\OneDrive - University of Canterbury\University\RH\HSS-Automation\CSV\Monitor.txt"
OUTFILE = r"C:\Users\henri\OneDrive - University of Canterbury\University\RH\HSS-Automation\CSV\CSV.txt"

def plot_flow(data):
    """Plots the angle of the paddle against the time passed"""
    fig1 = plt.figure("Figure 1")
    axes = plt.axes() 
    axes.plot(data[:,0], data[:,1])
    axes.plot(data[:,0], np.linspace(THRESHOLD, THRESHOLD, len(data[:,0])))
    axes.grid(True),
    axes.set_xlabel('Time (s)')
    axes.set_ylabel('Degrees')
    axes.set_title('Angle of potentiometer sensor')
    axes.set_xlim(0)
    axes.set_ylim(0)

def plot_prox(prox):
    """Plots the state of the proximity sensor during operation"""
    fig2 = plt.figure("Figure 2")
    plt.figure(2)
    axes = plt.axes() 
    axes.plot(prox[:,0],prox[:,1])
    axes.grid(True),
    axes.set_xlabel('Time (s)')
    axes.set_ylabel('Proximity sensor')
    axes.set_title('Reading of proximity sensor')
    axes.set_xlim(0)
    axes.set_ylim(0)

def open_file(filename):
    """Opens the file from a monitor"""
    infile = open(filename, 'r')
    file = infile.read()
    infile.close()
    return file

def convert(data):
    """Converts a list of strings into floats with the time converted to seconds"""
    empty = []
    for i in range(0, len(data)):
        line = (data[i][0].split(':'))
        time = float(line[0]) * 3600 + float(line[2]) + 60 * float(line[1])            
        empty.append([time, float(data[i][1])]) 
    empty.sort()
    return np.array(empty)

def proccess(lines):
    """Data processing for readable form"""
    blank = []
    empty = []
    for line in lines.split('\n'):
        sub = line.split(' ')
        if sub[2] =='F':
            blank.append([sub[0], sub[3]])
        elif sub[2] =='P':
            empty.append([sub[0], sub[3]])
    prox = convert(empty)
    prox[:,0] = prox[:,0] - prox[0][0]
    flow = convert(blank)
    flow[:,0] = flow[:,0] - flow[0][0]
    flow[:,1] = flow[:,1] * 360 / 1024  
    return flow, prox

def csv(flow, prox):
    """Writes the proccessed data to a CSV text file"""
    outfile = open(OUTFILE, 'w')
    outfile.write("Time, Flow\n")
    for i in flow:
        outfile.write(str(i[0]) + ',' + str(i[1]) + '\n')
    outfile.write("Time, Proximity\n")
    for i in prox:
        outfile.write(str(i[0]) + ',' + str(i[1]) + '\n')
    outfile.close

def main():
    """The main function"""
    lines = open_file(INFILE)
    flow, prox = proccess(lines)
    csv(flow, prox)
    plot_flow(flow)
    plot_prox(prox)
    plt.show()

main()


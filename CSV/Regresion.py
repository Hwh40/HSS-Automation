# File: regression.py
# Author: Henry Hall
# Date: 22/12/2022
# Description: Takes data from testing a paddle
#flow meter and plots a linear regression for the flow rate present. 

import numpy as np
import matplotlib.pyplot as plt
import scipy.linalg as linalg

ANGLE = [0, 40, 28]
FLOW = [0, 1.5, 0.5]

TABLE = np.sort(np.array([ANGLE, FLOW]).T, 0)
y_linear = lambda x, b_0, b_1: b_0 + b_1 * x

def linear_coef():
    """Finds the coefficients for a linear regression"""
    length = len(TABLE)
    ones = np.array([1] * length)
    A = np.array([ones, TABLE[:,0]]).T
    b = np.array(TABLE[:,1])
    lin = linalg.solve(A.T @ A, A.T @ b)
    return lin

def plot(b_1, b_0, func):
    """Plots the regression calculated as well as data points given"""
    axes = plt.axes()
    axes.plot(TABLE[:,0], TABLE[:,1], 'x')
    xs = np.linspace(TABLE[:,0][0], TABLE[:,0][-1], 1000)
    ys = func(xs, b_0, b_1)
    axes.plot(xs, ys)
    axes.grid(True)
    axes.set_title("Regression")
    axes.set_xlabel("Degrees")
    axes.set_ylabel("Flow Rate (L/S)")
    axes.set_xlim(0)
    axes.set_ylim(0)
    plt.show()

def details(b_1, b_0, func):
    """Finds the R squared value through sum of squares Method"""
    yhat = func(TABLE[:,0], b_0, b_1)
    ess = np.sum((yhat - np.mean(yhat)) ** 2) 
    tss = np.sum((TABLE[:,1] - np.mean(yhat)) ** 2)
    rss = np.sum((TABLE[:,1] - yhat) ** 2)
    rsq = ess / tss
    print(f'B0: {b_0}')
    print(f'B1: {b_1}')
    print()
    print(f'ESS: {ess}')
    print(f'TSS: {tss}')
    print(f'RSS: {rss}')
    print(f'R ^ 2: {rsq}')

def main():
    """The Main Function"""
    b_0, b_1 = linear_coef()
    details(b_1, b_0, y_linear)
    plot(b_1, b_0, y_linear)
    
main()
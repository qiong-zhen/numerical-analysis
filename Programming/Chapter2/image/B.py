import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def intNewton(x, xcp, f):
    divdiff = getdivideddiff(xcp, f)
    hatf = np.ones(len(x)) * f(xcp[0])
    for n in range(len(x)):
        t0 = 1
        for k in range(len(xcp) - 1):
            t0 = (x[n] - xcp[k]) * t0
            hatf[n] += divdiff[k] * t0
    return hatf


def getdivideddiff(xcp, f):
    divdiff = np.zeros(len(xcp) - 1)
    t = f(xcp)
    for k in range(len(xcp) - 1):
        num0 = t
        num1 = np.concatenate((np.ones(1), num0[0:-1]))
        k0 = k + 1
        den = np.concatenate((np.ones(k0), xcp[0:-k0]))
        t = (num0 - num1) / (xcp - den)
        divdiff[k] = t[k0]
    return divdiff


if __name__ == '__main__':
    work_file = './'
    # B
    csv_path = work_file + "Bout3.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    plt.plot(x_coords, y_coords)

    # parameters
    x = np.linspace(-5, 5, 1000)
    xcp = np.linspace(-5, 5, 9)

    # function to be interpolated
    f = lambda x: 1 / (np.power(x, 2) + 1)
    plt.plot(x, f(x))

    # Newton Interpolation
    hatf = intNewton(x, xcp, f)
    plt.plot(x, hatf)

    # plot control point
    for i in range(len(xcp)):
        plt.plot(xcp[i], f(xcp[i]), 'ro', markerfacecolor='none')
    plt.legend(["data", 'original', 'Newton', 'control point'])
    plt.title('Newton Interpolation')
    plt.show()
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def Eplot():
    x = np.arange(-2, 2, 0.01)
    y = np.arange(-2, 2, 0.01)
    x, y = np.meshgrid(x, y)
    z = np.power(x, 2) + np.power((3 / 2 * y - np.sqrt(np.abs(x))), 2) - 3
    plt.contour(x, y, z, 0)
    plt.title('Eplot Contour')
    plt.show()


if __name__ == '__main__':
    work_file = './'

    # F
    csv_path = work_file + "Fout.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    plt.plot(x_coords, y_coords)
    plt.title('Data from Fout.csv')
    plt.show()

    # Call Eplot
    Eplot()
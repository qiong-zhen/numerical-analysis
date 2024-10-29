import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

if __name__ == '__main__':
    work_file = './'

    # E
    # Plot for Eout1.csv
    csv_path = work_file + "Eout1.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    plt.plot(x_coords, y_coords, label='Eout1')

    # Plot for Eout2.csv
    csv_path = work_file + "Eout2.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    plt.plot(x_coords, y_coords, label='Eout2')

    plt.title('Data from Eout1.csv and Eout2.csv')
    plt.legend()
    plt.show()
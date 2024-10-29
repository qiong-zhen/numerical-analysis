import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

if __name__ == '__main__':
    work_file = './'
    # D
    csv_path = work_file + "Dout.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    plt.plot(x_coords, y_coords)
    plt.title('Data from Dout.csv')
    plt.show()
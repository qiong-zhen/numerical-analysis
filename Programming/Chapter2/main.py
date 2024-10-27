import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


def Eplot():
	# 设置x和y的坐标范围
    x=np.arange(-2,2,0.01)
    y=np.arange(-2,2,0.01)
    # 转化为网格
    x,y=np.meshgrid(x,y)
    z=np.power(x,2)+np.power((3/ 2 * y - np.sqrt(np.abs(x))),2)-3
    plt.contour(x,y,z,0)
    plt.show()
def intNewton(x,xcp,f):
    divdiff = getdivideddiff(xcp,f)
    hatf = np.ones(len(x))*f(xcp[0])
    for n in range(len(x)):
        t0 = 1
        for k in range(len(xcp)-1):
            # Newton
            t0 = (x[n]-xcp[k])*t0
            hatf[n] += divdiff[k]*t0
    return hatf

def getdivideddiff(xcp,f):
    divdiff = np.zeros(len(xcp)-1)
    t = f(xcp)
    for k in range(len(xcp)-1):
        num0 = t
        num1 = np.concatenate((np.ones(1),num0[0:-1]))
        k0 = k+1
        den = np.concatenate((np.ones(k0),xcp[0:-k0]))
        t = (num0-num1)/(xcp-den)
        divdiff[k] = t[k0]
    return divdiff

if __name__ == '__main__':
    work_file = 'D:/Desktop/Code/'
    #B
    csv_path = work_file + "Bout3.csv"
    data = pd.read_csv(csv_path)

    x_coords = data['x']
    y_coords = data['y']
    # print(y_coords)
    plt.plot(x_coords, y_coords)
    # parameters
    x = np.linspace(-5,5,1000)          # 待插值点
    xcp = np.linspace(-5,5,9)     # 插值节点的函数值已知
    # function to be interpolated
    f = lambda x: 1 / (np.power(x,2) + 1)
    plt.plot(x,f(x))
    ##Newton Interpolation
    hatf = intNewton(x,xcp,f)
    plt.plot(x,hatf)
    # plot control point
    for i in range(len(xcp)):
        plt.plot(xcp[i],f(xcp[i]),'ro',markerfacecolor='none')
    plt.legend(["data",'original','Newton','control point'])
    plt.title('Newton Interpolation')
    plt.show()

    # C
    # csv_path = work_file + "CoutCheb3.csv"
    # data = pd.read_csv(csv_path)
    #
    # x_coords = data['x']
    # y_coords = data['y']
    # # print(y_coords)
    # plt.plot(x_coords, y_coords)
    # # parameters
    # x = np.linspace(-1,1,1000)          # 待插值点
    # xcp = np.linspace(-1,1,16)     # 插值节点的函数值已知
    # # function to be interpolated
    # f = lambda x: 1 / (25 * np.power(x,2) + 1)
    # plt.plot(x,f(x))
    # ##Newton Interpolation
    # hatf = intNewton(x,xcp,f)
    # plt.plot(x,hatf)
    # # plot control point
    # for i in range(len(xcp)):
    #     plt.plot(xcp[i],f(xcp[i]),'ro',markerfacecolor='none')
    # plt.legend(["data",'original','Newton','control point'])
    # plt.title('Newton Interpolation')
    # plt.show()

    # D
    # csv_path = work_file + "Dout.csv"
    # data = pd.read_csv(csv_path)
    #
    # x_coords = data['x']
    # y_coords = data['y']
    # # print(y_coords)
    # plt.plot(x_coords, y_coords)
    # plt.show()

    # # E
    # csv_path = work_file + "Eout1.csv"
    # data = pd.read_csv(csv_path)
    #
    # x_coords = data['x']
    # y_coords = data['y']
    # # print(y_coords)
    # plt.plot(x_coords, y_coords)
    # csv_path = work_file + "Eout2.csv"
    # data = pd.read_csv(csv_path)
    #
    # x_coords = data['x']
    # y_coords = data['y']
    # # print(y_coords)
    # plt.plot(x_coords, y_coords)
    # plt.show()

    # # F
    # csv_path = work_file + "Fout.csv"
    # data = pd.read_csv(csv_path)
    #
    # x_coords = data['x']
    # y_coords = data['y']
    # # print(y_coords)
    # plt.plot(x_coords, y_coords)
    # Eplot()
    # plt.show()

import numpy as np
import matplotlib.pyplot as plt
import os

# 创建figure目录
if not os.path.exists('figure'):
    os.makedirs('figure')

def plot_case1():
    # 读取三点情况的数据
    data = np.loadtxt('figure/divided_diff_1.txt', skiprows=1)
    x = data[:, 0]
    f0 = data[:, 1]  # f[0]
    f1 = data[:, 2]  # f[1]
    f2 = data[:, 3]  # f[2]
    f01 = data[:, 4]  # f[0,1]
    f12 = data[:, 5]  # f[1,2]
    f012 = data[:, 6]  # f[0,1,2]

    plt.figure(figsize=(15, 10))
    
    # 绘制函数值
    plt.subplot(311)
    plt.plot(x, f0, 'r-', label='f[0]')
    plt.plot(x, f1, 'g-', label='f[1]')
    plt.plot(x, f2, 'b-', label='f[2]')
    plt.grid(True)
    plt.legend()
    plt.title('Function Values')
    plt.xlim(0, 2)  # 限制x轴范围在[0,2]
    
    # 绘制一阶差商
    plt.subplot(312)
    plt.plot(x, f01, 'r-', label='f[0,1]')
    plt.plot(x, f12, 'g-', label='f[1,2]')
    plt.grid(True)
    plt.legend()
    plt.title('First Order Divided Differences')
    plt.xlim(0, 2)  # 限制x轴范围在[0,2]
    
    # 绘制二阶差商
    plt.subplot(313)
    plt.plot(x, f012, 'r-', label='f[0,1,2]')
    plt.grid(True)
    plt.legend()
    plt.title('Second Order Divided Difference')
    plt.xlim(0, 2)  # 限制x轴范围在[0,2]
    
    plt.tight_layout()
    plt.savefig('figure/divided_diff_case1.png')
    plt.close()

def plot_case2():
    # 读取四点情况的数据
    data = np.loadtxt('figure/divided_diff_2.txt', skiprows=1)
    x = data[:, 0]
    f0 = data[:, 1]   # f[0]
    f1 = data[:, 2]   # f[1]
    f2 = data[:, 3]   # f[2]
    f3 = data[:, 4]   # f[3]
    f01 = data[:, 5]  # f[0,1]
    f12 = data[:, 6]  # f[1,2]
    f23 = data[:, 7]  # f[2,3]
    f012 = data[:, 8] # f[0,1,2]
    f123 = data[:, 9] # f[1,2,3]
    f0123 = data[:, 10] # f[0,1,2,3]

    plt.figure(figsize=(15, 12))
    
    # 绘制函数值
    plt.subplot(411)
    plt.plot(x, f0, 'r-', label='f[0]')
    plt.plot(x, f1, 'g-', label='f[1]')
    plt.plot(x, f2, 'b-', label='f[2]')
    plt.plot(x, f3, 'y-', label='f[3]')
    plt.grid(True)
    plt.legend()
    plt.title('Function Values')
    plt.xlim(0, 3)  # 限制x轴范围在[0,3]
    
    # 绘制一阶差商
    plt.subplot(412)
    plt.plot(x, f01, 'r-', label='f[0,1]')
    plt.plot(x, f12, 'g-', label='f[1,2]')
    plt.plot(x, f23, 'b-', label='f[2,3]')
    plt.grid(True)
    plt.legend()
    plt.title('First Order Divided Differences')
    plt.xlim(0, 3)  # 限制x轴范围在[0,3]
    
    # 绘制二阶差商
    plt.subplot(413)
    plt.plot(x, f012, 'r-', label='f[0,1,2]')
    plt.plot(x, f123, 'g-', label='f[1,2,3]')
    plt.grid(True)
    plt.legend()
    plt.title('Second Order Divided Differences')
    plt.xlim(0, 3)  # 限制x轴范围在[0,3]
    
    # 绘制三阶差商
    plt.subplot(414)
    plt.plot(x, f0123, 'r-', label='f[0,1,2,3]')
    plt.grid(True)
    plt.legend()
    plt.title('Third Order Divided Difference')
    plt.xlim(0, 3)  # 限制x轴范围在[0,3]
    
    plt.tight_layout()
    plt.savefig('figure/divided_diff_case2.png')
    plt.close()

if __name__ == "__main__":
    try:
        plot_case1()
        plot_case2()
    except Exception as e:
        print(f"Error: {e}") 
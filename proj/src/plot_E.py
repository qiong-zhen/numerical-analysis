import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import os

# 创建figure目录
if not os.path.exists('figure'):
    os.makedirs('figure')

def plot_curve2(N):
    data = np.loadtxt(f'../include/curve2_N{N}.txt', skiprows=1)
    t = data[:, 0]
    uniform_x, uniform_y = data[:, 1], data[:, 2]
    chordal_x, chordal_y = data[:, 3], data[:, 4]
    
    plt.figure(figsize=(12, 5))
    
    # 均匀参数化
    plt.subplot(121)
    plt.plot(uniform_x, uniform_y, 'b-', label='Uniform')
    plt.grid(True)
    plt.title(f'Uniform Parameterization (N={N})')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    
    # 弦长参数化
    plt.subplot(122)
    plt.plot(chordal_x, chordal_y, 'r-', label='Chordal')
    plt.grid(True)
    plt.title(f'Chordal Parameterization (N={N})')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    
    plt.tight_layout()
    plt.savefig(f'figure/curve2_N{N}.png')
    plt.close()

def plot_curve3(N):
    data = np.loadtxt(f'fig../include/curve3_N{N}.txt', skiprows=1)
    t = data[:, 0]
    uniform_x, uniform_y, uniform_z = data[:, 1], data[:, 2], data[:, 3]
    chordal_x, chordal_y, chordal_z = data[:, 4], data[:, 5], data[:, 6]
    
    fig = plt.figure(figsize=(12, 5))
    
    # 均匀参数化
    ax1 = fig.add_subplot(121, projection='3d')
    ax1.plot(uniform_x, uniform_y, uniform_z, 'b-', label='Uniform')
    ax1.set_title(f'Uniform Parameterization (N={N})')
    ax1.set_xlabel('x')
    ax1.set_ylabel('y')
    ax1.set_zlabel('z')
    ax1.legend()
    
    # 弦长参数化
    ax2 = fig.add_subplot(122, projection='3d')
    ax2.plot(chordal_x, chordal_y, chordal_z, 'r-', label='Chordal')
    ax2.set_title(f'Chordal Parameterization (N={N})')
    ax2.set_xlabel('x')
    ax2.set_ylabel('y')
    ax2.set_zlabel('z')
    ax2.legend()
    
    plt.tight_layout()
    plt.savefig(f'figure/curve3_N{N}.png')
    plt.close()

if __name__ == "__main__":
    try:
        N_values = [10, 40, 160]
        
        # 绘制r2(t)曲线
        for N in N_values:
            plot_curve2(N)
            
        # 绘制r3(t)曲线
        for N in N_values:
            plot_curve3(N)
            
    except Exception as e:
        print(f"Error: {e}") 
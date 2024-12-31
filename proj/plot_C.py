import numpy as np
import matplotlib.pyplot as plt
import os

# 创建figure目录
if not os.path.exists('figure'):
    os.makedirs('figure')

def plot_comparison(boundary_type):
    # 读取数据
    data = np.loadtxt(f'figure/spline_data_{boundary_type}.txt', skiprows=1)
    x = data[:, 0]
    y_exact = data[:, 1]
    y_spline1 = data[:, 2]  # Theorem 3.57
    y_spline2 = data[:, 3]  # Theorem 3.58

    plt.figure(figsize=(15, 5))

    # Theorem 3.57结果
    plt.subplot(131)
    plt.plot(x, y_exact, 'k-', label='Exact', linewidth=2)
    mask1 = ~np.isnan(y_spline1)
    plt.plot(x[mask1], y_spline1[mask1], 'r--', 
             label='Theorem 3.57', linewidth=1.5)
    plt.grid(True)
    plt.legend()
    plt.title(f'Theorem 3.57 ({boundary_type})')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.xlim(-5, 5)
    plt.ylim(-0.1, 1.1)

    # Theorem 3.58结果
    plt.subplot(132)
    plt.plot(x, y_exact, 'k-', label='Exact', linewidth=2)
    mask2 = ~np.isnan(y_spline2)
    plt.plot(x[mask2], y_spline2[mask2], 'b--', 
             label='Theorem 3.58', linewidth=1.5)
    plt.grid(True)
    plt.legend()
    plt.title(f'Theorem 3.58 ({boundary_type})')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.xlim(-5, 5)
    plt.ylim(-0.1, 1.1)

    # 误差比较
    plt.subplot(133)
    error1 = np.abs(y_spline1[mask1] - y_exact[mask1])
    error2 = np.abs(y_spline2[mask2] - y_exact[mask2])
    plt.semilogy(x[mask1], error1, 'r-', label='Theorem 3.57')
    plt.semilogy(x[mask2], error2, 'b-', label='Theorem 3.58')
    plt.grid(True)
    plt.legend()
    plt.title('Error Comparison')
    plt.xlabel('x')
    plt.ylabel('Error')

    plt.tight_layout()
    plt.savefig(f'figure/spline_comparison_{boundary_type}.png')
    plt.close()

# 生成不同边界条件的图片
plot_comparison('natural') 
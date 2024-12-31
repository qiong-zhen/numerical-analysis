import numpy as np
import matplotlib.pyplot as plt
import os

# 创建figure目录
if not os.path.exists('figure'):
    os.makedirs('figure')

# 读取数据
data = np.loadtxt('../include/spline_data1_D.txt', skiprows=1)
x = data[:, 0]
y_exact = data[:, 1]
y_spline1 = data[:, 2]  # Theorem 3.57
y_spline2 = data[:, 3]  # Theorem 3.58

plt.figure(figsize=(15, 5))

# 插值结果比较
plt.subplot(121)
plt.plot(x, y_exact, 'k-', label='Exact', linewidth=2)
mask1 = ~np.isnan(y_spline1)
mask2 = ~np.isnan(y_spline2)
plt.plot(x[mask1], y_spline1[mask1], 'r--', label='Theorem 3.57', linewidth=1.5)
plt.plot(x[mask2], y_spline2[mask2], 'b--', label='Theorem 3.58', linewidth=1.5)
plt.grid(True)
plt.legend()
plt.title('Interpolation Comparison')
plt.xlabel('x')
plt.ylabel('y')
plt.xlim(-5, 5)
plt.ylim(-0.1, 1.1)

# 误差分析
plt.subplot(122)
error1 = np.abs(y_spline1[mask1] - y_exact[mask1])
error2 = np.abs(y_spline2[mask2] - y_exact[mask2])
plt.semilogy(x[mask1], error1, 'r-', label='Theorem 3.57')
plt.semilogy(x[mask2], error2, 'b-', label='Theorem 3.58')
plt.grid(True)
plt.legend()
plt.title('Error Analysis')
plt.xlabel('x')
plt.ylabel('Error')

plt.tight_layout()
plt.savefig('figure/spline_comparison_D.png')
plt.close() 
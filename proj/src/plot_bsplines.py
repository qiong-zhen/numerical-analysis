import numpy as np
import matplotlib.pyplot as plt

# 读取数据
data = np.loadtxt('../include/bspline_results.txt', skiprows=1)
x = data[:, 0]
y_exact = data[:, 1]
y_linear = data[:, 2]
y_quadratic = data[:, 3]
y_cubic = data[:, 4]

# 创建图形
plt.figure(figsize=(12, 8))

# 绘制不同阶数的B样条结果
plt.plot(x, y_exact, 'k-', label='Exact', linewidth=2)
plt.plot(x, y_linear, 'r--', label='Linear B-spline', linewidth=1.5)
plt.plot(x, y_quadratic, 'g--', label='Quadratic B-spline', linewidth=1.5)
plt.plot(x, y_cubic, 'b--', label='Cubic B-spline', linewidth=1.5)

plt.grid(True)
plt.legend()
plt.title('Comparison of B-spline Interpolation Methods')
plt.xlabel('x')
plt.ylabel('y')

# 保存图形
plt.savefig('bspline_comparison.png')
plt.close() 
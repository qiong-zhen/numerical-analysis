import numpy as np
import matplotlib.pyplot as plt

# 读取数据
data = np.loadtxt('interpolation_results.txt', skiprows=1)
x = data[:, 0]
y_exact = data[:, 1]
y_linear = data[:, 2]
y_cubic = data[:, 3]

# 绘图
plt.figure(figsize=(10, 6))
plt.plot(x, y_exact, 'k-', label='Exact')
plt.plot(x, y_linear, 'r--', label='Linear')
plt.plot(x, y_cubic, 'b--', label='Cubic')
plt.grid(True)
plt.legend()
plt.title('Comparison of Interpolation Methods')
plt.xlabel('x')
plt.ylabel('y')
plt.savefig('interpolation_comparison.png')
plt.close() 
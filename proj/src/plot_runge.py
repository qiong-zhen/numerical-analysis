import numpy as np
import matplotlib.pyplot as plt
import os

# 创建figure目录
if not os.path.exists('figure'):
    os.makedirs('figure')

N_values = [6, 11, 21, 41, 81]
colors = ['b', 'g', 'r', 'c', 'm']

# 为每个N生成单独的图片
for N in N_values:
    plt.figure(figsize=(10, 6))
    
    data = np.loadtxt(f'figure/runge_data_{N}.txt', skiprows=1)
    x = data[:, 0]
    y_exact = data[:, 1]
    y_spline = data[:, 2]
    
    plt.plot(x, y_exact, 'k-', label='Exact')
    plt.plot(x, y_spline, 'r--', label=f'N={N}')
    
    plt.grid(True)
    plt.legend()
    plt.title(f'Runge Function Interpolation (N={N})')
    plt.xlabel('x')
    plt.ylabel('y')
    
    plt.savefig(f'figure/runge_interpolation_N{N}.png')
    plt.close()

# 生成所有N的对比图
plt.figure(figsize=(15, 10))

for N, color in zip(N_values, colors):
    data = np.loadtxt(f'figure/runge_data_{N}.txt', skiprows=1)
    x = data[:, 0]
    y_exact = data[:, 1]
    y_spline = data[:, 2]
    
    plt.plot(x, y_exact, 'k-', label='Exact' if N == 6 else None)
    plt.plot(x, y_spline, f'{color}--', label=f'N={N}')

plt.grid(True)
plt.legend()
plt.title('Runge Function Interpolation (All N)')
plt.xlabel('x')
plt.ylabel('y')

plt.savefig('figure/runge_interpolation_comparison.png')
plt.close()

# 绘制收敛率
errors = np.loadtxt('figure/convergence_data.txt')
plt.figure(figsize=(10, 6))
plt.loglog(N_values, errors, 'bo-')
plt.grid(True)
plt.xlabel('N')
plt.ylabel('Max Error')
plt.title('Convergence Rate')
plt.savefig('figure/convergence_rate.png')
plt.close() 
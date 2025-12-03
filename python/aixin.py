import matplotlib.pyplot as plt
import numpy as np

# 生成爱心曲线坐标
t = np.linspace(0, 2 * np.pi, 300)
x = 16 * np.sin(t) ** 3
y = 13 * np.cos(t) - 5 * np.cos(2 * t) - 2 * np.cos(3 * t) - np.cos(4 * t)

fig, ax = plt.subplots()
ax.fill(x, y, color='pink')

ax.set_xlim([-20, 20])
ax.set_ylim([-20, 20])
ax.set_aspect(1)
ax.set_title("A Pink Heart")
ax.set_xlabel("X")
ax.set_ylabel("Y")
plt.show()
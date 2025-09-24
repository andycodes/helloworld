import matplotlib.pyplot as plt
import numpy as np

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

# 创建数据
x = np.arange(1, 11)  # x轴数据：1到10
y = np.array([3, 5, 7, 2, 8, 10, 4, 6, 9, 5])  # y轴数据

# 创建图形和坐标轴
plt.figure(figsize=(10, 6))

# 绘制折线图
plt.plot(x, y, marker='o', linestyle='-', color='#2E86AB', linewidth=2, markersize=8)

# 在每个数据点上标注Y值
for i, (xi, yi) in enumerate(zip(x, y)):
    # 根据点的位置调整标注位置，避免重叠
    vertical_offset = 0.3 if yi < max(y) - 2 else -0.5
    plt.annotate(f'{yi}', 
                 (xi, yi), 
                 textcoords="offset points", 
                 xytext=(0, 10 if vertical_offset > 0 else -15), 
                 ha='center',
                 fontsize=10,
                 bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))

# 添加标题和标签
plt.title('折线图示例 - 带Y值标注', fontsize=14, fontweight='bold')
plt.xlabel('X轴', fontsize=12)
plt.ylabel('Y轴', fontsize=12)

# 设置网格
plt.grid(True, linestyle='--', alpha=0.7)

# 调整布局
plt.tight_layout()

# 显示图形
plt.show()
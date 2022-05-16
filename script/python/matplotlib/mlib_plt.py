"""
    默认的是竖值条形图
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib

# 将全局的字体设置为黑体
matplotlib.rcParams['font.family'] = 'SimHei'

# 数据
N = 5
y = [20, 10, 30, 25, 15]
x = np.arange(N)

# 绘图 x x轴， height 高度, 默认：color="blue", width=0.8
p1 = plt.bar(x, height=y, width=0.5, )

# 展示图形
plt.show()

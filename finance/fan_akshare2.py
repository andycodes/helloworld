import mplfinance as mpf
import pandas as pd

# 创建日期索引
index_date = pd.DatetimeIndex(['20210906', '20210907', '20210908', '20210909'])
# 随便创建数据
data = pd.DataFrame({
    'Open': [1, 2, 3, 4], 
    'High': [2, 3, 4, 5], 
    'Low' : [0.5, 1, 2, 2],
    'Close': [2, 3, 4, 3]
}, index=index_date)
# 调用plot函数 进行绘图
mpf.plot(data, type='candle', mav=(2, 3))
#mpf.plot(data,type='line')
#type还可以为：renko、pnf。
#mav参数可以添加移动平均线，更好的看趋势。还可以添加多条移动平均线：

import akshare as ak
import pandas as pd

# 1. 获取港股历史行情数据
# 请将 "00700" 替换为你需要的股票代码
df = ak.stock_hk_hist(symbol="00700", period="daily", start_date="20230101", end_date="20231001")

# 2. 查看数据的列名和前几行，确认数据结构
print("数据的列名：")
print(df.columns.tolist())
print("\n数据的前几行：")
print(df.head())

# 3. 提取日期列（这里假设列名是'日期'）
# 请根据上一步打印出的列名进行调整
dates = df['日期']

# 4. 打印提取出的日期
print("\n提取的日期数据：")
print(dates)
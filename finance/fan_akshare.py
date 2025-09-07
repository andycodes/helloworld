import akshare as ak

# 获取腾讯控股（0700.HK）的历史行情数据
stock_hk_hist = ak.stock_hk_hist(symbol="00700", period="daily", start_date="20250901", end_date="20250907")
print(stock_hk_hist.head())

# 获取港股实时行情（示例）
# 注意：AkShare的实时数据接口可能因数据源变动而调整，请查阅其最新文档
# stock_hk_spot = ak.stock_hk_spot() 
# print(stock_hk_spot.head())
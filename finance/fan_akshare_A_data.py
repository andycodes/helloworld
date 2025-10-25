import akshare as ak

stock_yjbb_em_df = ak.stock_yjbb_em(date="20250930")
print(stock_yjbb_em_df)
roe_df = stock_yjbb_em_df[['股票代码', '股票简称', '净资产收益率']]

# 按 ROE 倒序排列
roe_df_sorted = roe_df.sort_values(by='净资产收益率', ascending=False)

roe_df_sorted.to_csv("stock_yjbb_em.csv", index=False, encoding='utf-8-sig')

# 打印结果
print(roe_df_sorted)

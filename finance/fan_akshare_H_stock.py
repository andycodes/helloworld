import akshare as ak
import matplotlib.pyplot as plt
from datetime import datetime, date, timedelta
import pandas as pd

stocks_l = []
def stock_init():
    stocks_l.append(["tengxun", "00700"])
    stocks_l.append(["ali", "09988"])
    stocks_l.append(["xiaoimi", "01810"])
    stocks_l.append(["meituan", "03690"])  
    stocks_l.append(["dipingxian", "09660"])  
    stocks_l.append(["zhongxinguoji", "00981"])  
    stocks_l.append(["huahong", "01347"])  
    stocks_l.append(["fudan", "01385"])  

com_name = []
roe_v = []
pe_v = []

if __name__ == "__main__":
    stock_init()
    for stock in stocks_l:
        stock_hk_financial_indicator_em_df = ak.stock_hk_financial_indicator_em(symbol=stock[1])
        pb = stock_hk_financial_indicator_em_df['市净率']
        pe = stock_hk_financial_indicator_em_df['市盈率']
        roe = pb.values/pe.values
        roe_show = int(roe*100)
        com_name.append(stock[0])
        roe_v.append(roe_show)
        pe_v.append(int(pe.values))

    # 使用 pandas 数据框
    df = pd.DataFrame({
        'Category': com_name,
        'ROE': roe_v,
        'PE': pe_v
    })

    # 绘制柱状图
    ax = df.plot(x='Category', y=['ROE', 'PE'], kind='bar', figsize=(10, 6))

    # 使用 bar_label 添加标签 (推荐方法)
    ax.bar_label(ax.containers[0], fmt='%.0f', padding=3, fontsize=12)
    ax.bar_label(ax.containers[1], fmt='%.0f', padding=3, fontsize=12)
    
    title_name = 'stock'
    plt.title(title_name)
    plt.ylabel('Values')
    plt.xticks(rotation=0)
    current_year_month = datetime.now().strftime("%Y%m")
    full_path = 'C:/family/finance/' + title_name+ current_year_month +'.png'
    plt.savefig(full_path,
           dpi=300,
           bbox_inches='tight',
           facecolor='white',
           edgecolor='black')
    plt.show()
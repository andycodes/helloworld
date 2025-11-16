from datetime import datetime, date, timedelta
import mplfinance as mpf
import pandas as pd

def get_n_days_ago(n):
    n_days_ago = datetime.now() - timedelta(days=n)
    return n_days_ago.strftime("%Y%m%d")

def get_date_today():
    today = date.today()
    return today.strftime("%Y%m%d")

def plot_show(stock_hk_hist):
    dates = stock_hk_hist['日期']
    open_prices = stock_hk_hist['开盘'].tolist()  # 改名为 open_prices，避免与内置函数open冲突
    close_prices = stock_hk_hist['收盘'].tolist()  # 改名为 close_prices
    low_prices = stock_hk_hist['最低'].tolist()    # 改名为 low_prices
    high_prices = stock_hk_hist['最高'].tolist()   # 改名为 high_prices
    volume = stock_hk_hist['成交量'].tolist()      # 添加成交量数据
    
    # 创建日期索引
    index_date = pd.DatetimeIndex(dates)
    
    # 创建包含所有必要列的数据框，包括Volume
    data = pd.DataFrame({
        'Open': open_prices, 
        'High': high_prices, 
        'Low': low_prices,
        'Close': close_prices,
        'Volume': volume  # 添加Volume列
    }, index=index_date)
    
    # 设置蜡烛图颜色
    mc = mpf.make_marketcolors(
        up='r',           # 上涨为红色
        down='g',         # 下跌为绿色
        edge='inherit',   # 边框继承up/down的颜色
        wick='inherit',   # 影线继承up/down的颜色
        volume='inherit'  # 成交量继承up/down的颜色
    )
    
    my_style = mpf.make_mpf_style(marketcolors=mc)
    
    # 绘制蜡烛图，包含成交量
    mpf.plot(data, 
             type='candle', 
             title='Xiaomi Stock', 
             style=my_style, 
             volume=True,  # 现在可以正确显示成交量了
             mav=(5, 10, 20))  # 添加5日、10日和20日移动平均线


    


#https://cloud.tencent.cn/developer/article/2144798?policyId=1003
#https://cloud.tencent.cn/developer/article/2454419?policyId=1003
import akshare as ak
from datetime import datetime, date, timedelta
import mplfinance as mpf
import pandas as pd

stocks_l = []
def stock_init():
    stocks_l.append(["xiaoimi", "01810"])

def get_n_days_ago(n):
    n_days_ago = datetime.now() - timedelta(days=n)
    return n_days_ago.strftime("%Y%m%d")

def get_date_today():
    today = date.today()
    return today.strftime("%Y%m%d")

if __name__ == "__main__":
    stock_init()
    for stock in stocks_l:
        print(stock[0], stock[1])
        stock_hk_hist = ak.stock_hk_hist(symbol=stock[1], period="daily", start_date=get_n_days_ago(365), end_date=get_date_today())
        print(stock_hk_hist.head())
        dates = stock_hk_hist['日期']
        open = stock_hk_hist['开盘'].tolist()
        close = stock_hk_hist['收盘'].tolist()
        low = stock_hk_hist['最低'].tolist()
        highs = stock_hk_hist['最高'].tolist()
        print(type(open))
        print(type([1, 2, 3, 4]))
        # 创建日期索引
        index_date = pd.DatetimeIndex(dates)
        # 随便创建数据
        data = pd.DataFrame({
            'Open': open, 
            'High': highs, 
            'Low' : low,
            'Close': close
        }, index=index_date)
        # 调用plot函数 进行绘图
        mpf.plot(data, type='candle')
        #mpf.plot(data,type='line')
        #type还可以为：renko、pnf。
        #mav参数可以添加移动平均线，更好的看趋势。还可以添加多条移动平均线：

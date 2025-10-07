import akshare as ak
from datetime import datetime, date, timedelta
import mplfinance as mpf
import pandas as pd

stocks_l = []
def stock_init():
    stocks_l.append(["tengxun", "00700"])
    stocks_l.append(["ali", "09988"])
    stocks_l.append(["weilai", "09866"])
    stocks_l.append(["xiaopeng", "09868"])
    stocks_l.append(["lixiang", "00215"])
    stocks_l.append(["xiaoimi", "01810"])
    stocks_l.append(["weituan", "03690"])  
    stocks_l.append(["dipingxian", "09660"])  

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
        stock_hk_hist = ak.stock_hk_hist(symbol=stock[1], period="daily", start_date=get_n_days_ago(7), end_date=get_date_today())
        print(stock_hk_hist.head())
        data1 = stock_hk_hist.loc['2025-10-01 00:00:00+00:00':'2025-10-11 00:00:00+00:00']
        mpf.plot(data1, type='candle', mav=(200, 300, 350), volume=True)

#https://cloud.tencent.cn/developer/article/2144798?policyId=1003
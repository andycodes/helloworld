import akshare as ak
from datetime import datetime, date, timedelta

stocks = ["00700"]

def get_n_days_ago(n):
    n_days_ago = datetime.now() - timedelta(days=n)
    return n_days_ago.strftime("%Y%m%d")

def get_date_today():
    today = date.today()
    return today.strftime("%Y%m%d")

for stock in stocks:
    stock_hk_hist = ak.stock_hk_hist(symbol=stock, period="daily", start_date=get_n_days_ago(7), end_date=get_date_today())
    print(stock_hk_hist.head())

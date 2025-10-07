import akshare as ak
from datetime import datetime, date, timedelta

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
        stock_hk_hist = ak.stock_hk_hist(symbol=stock[1], period="daily", start_date=get_n_days_ago(7), end_date=get_date_today())
        print(stock_hk_hist)


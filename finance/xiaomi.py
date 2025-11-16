import stock_show_lib
import akshare as ak

stock = ["xiaomi", "01810"]

if __name__ == "__main__":
    print(stock[0], stock[1])
    stock_hk_hist = ak.stock_hk_hist(symbol=stock[1], period="daily", start_date=stock_show_lib.get_n_days_ago(365), end_date=stock_show_lib.get_date_today())
    print(stock_hk_hist.head())
    stock_show_lib.plot_show(stock_hk_hist)
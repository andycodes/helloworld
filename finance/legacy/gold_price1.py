import akshare as ak
import stock_show_lib1

if __name__ == "__main__":
    stock_hk_hist = ak.spot_golden_benchmark_sge()
    print(stock_hk_hist.head())
    stock_show_lib1.plot_show(stock_hk_hist)
import akshare as ak
import mplfinance as mpf
import pandas as pd


def get_gold_data():
    # 获取黄金延期合约 Au(T+D) 的历史数据
    return ak.spot_hist_sge(symbol='Au(T+D)')  

def plot_gold_data(last_3_months):
    dates = last_3_months['date']
    open_prices = last_3_months['open'].tolist()  # 改名为 open_prices，避免与内置函数open冲突
    close_prices = last_3_months['close'].tolist()  # 改名为 close_prices
    low_prices = last_3_months['low'].tolist()    # 改名为 low_prices
    high_prices = last_3_months['high'].tolist()   # 改名为 high_prices
    
    # 创建日期索引
    index_date = pd.DatetimeIndex(dates)
    
    # 创建包含所有必要列的数据框，包括Volume
    data = pd.DataFrame({
        'Open': open_prices, 
        'High': high_prices, 
        'Low': low_prices,
        'Close': close_prices,
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
             title='gold price', 
             style=my_style, 
             mav=(5, 10, 20))  # 添加5日、10日和20日移动平均线
    
    mpf.show()

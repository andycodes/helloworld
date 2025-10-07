import requests
import copy
from bs4 import BeautifulSoup

import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd


def scrape_website(url, params=None):
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
    }
    
    try:
        response = requests.get(url, headers=headers, params=params, timeout=10)
        response.raise_for_status()
        
        # 检测编码
        if response.encoding == 'ISO-8859-1':
            response.encoding = response.apparent_encoding
        
        soup = BeautifulSoup(response.text, 'html.parser')
        return soup
        
    except requests.exceptions.RequestException as e:
        print(f"Error scraping website: {e}")
        return None

def get_car_sale_date(soup):
    blue_th_tags = soup.find_all('th', class_='blue')
    contents = [tag.get_text(strip=True) for tag in reversed(blue_th_tags)]
    print("日期:", contents)
    return contents

def get_car_sale_data(soup, months):
    table = soup.find('table')
    data = []

    if table:
        for row in table.find_all('tr'):
            columns = row.find_all('td')
            if columns:
                row_data = [col.get_text(strip=True) for col in columns]
                data.append(row_data)

    #print("表格数据:", data)
    month_sale_str = list(reversed(data[1][2:months+2]))
    month_sale = [int(x) for x in month_sale_str]
    print("表格数据:", month_sale)
    return month_sale

def lineplot_show(who, months, values):
    data = {'X': months, 'Y': values}
    df = pd.DataFrame(data)
    # 绘制折线图
    sns.lineplot(x='X', y='Y', data=df, label=who)

    # 在每个数据点上标注Y值
    for i, (xi, yi) in enumerate(zip(months, values)):
        # 根据点的位置调整标注位置，避免重叠
        vertical_offset = 0.3 if yi < max(values) - 2 else -0.5
        plt.annotate(f'{yi}', 
                    (xi, yi), 
                    textcoords="offset points", 
                    xytext=(0, 10 if vertical_offset > 0 else -15), 
                    ha='center',
                    fontsize=10,
                    bbox=dict(boxstyle="round,pad=0.3", facecolor="white", alpha=0.8))



if __name__ == "__main__":
    weblist = []
    weblist.append(["xiaomi", 'https://price.pcauto.com.cn/salescar/nb8714/'])
    weblist.append(["lixiang", 'https://price.pcauto.com.cn/salescar/nb7721/'])
    weblist.append(["lingpao", 'https://price.pcauto.com.cn/salescar/nb7421/'])
    weblist.append(["weilai", 'https://price.pcauto.com.cn/salescar/nb7250/'])
    weblist.append(["xiaopeng", 'https://price.pcauto.com.cn/salescar/nb7210/'])

    for web in weblist:
        soup = scrape_website(web[1])
        if soup:
            title = soup.find('title')
            print(title.text if title else "No title found")

        months = get_car_sale_date(soup)
        values = get_car_sale_data(soup, len(months))
        print("表格数据1:", values)
        lineplot_show(web[0], months, values)

    plt.title('car sale', fontsize=14, fontweight='bold')
    plt.show()

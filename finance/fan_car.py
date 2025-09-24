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
    month_sale = list(reversed(data[1][2:months+2]))
    print("表格数据:", month_sale)
    return month_sale

def picture_show(months, values):
    # 创建一个示例数据框
    #data = {'X': [1, 2, 3, 4, 5], 'Y': [5, 2, 3, 2, 1]}
    data = {'X': months, 'Y': values}
    df = pd.DataFrame(data)
    # 绘制折线图
    sns.lineplot(x='X', y='Y', data=df)
    plt.gca().invert_yaxis()
    plt.show()

if __name__ == "__main__":
    soup = scrape_website('https://price.pcauto.com.cn/salescar/nb8714/')
    if soup:
        title = soup.find('title')
        print(title.text if title else "No title found")

    months = get_car_sale_date(soup)
    values = get_car_sale_data(soup, len(months))
    print("表格数据1:", values)
    picture_show(months, values)






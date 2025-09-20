import requests
from bs4 import BeautifulSoup

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

# 使用示例
soup = scrape_website('https://price.pcauto.com.cn/salescar/nb8714/')
if soup:
    title = soup.find('title')
    print(title.text if title else "No title found")

# 提取表格数据
table = soup.find('table')

data = []

if table:
    for row in table.find_all('tr'):
        columns = row.find_all('td')
        if columns:
            row_data = [col.get_text(strip=True) for col in columns]
            data.append(row_data)

print("表格数据:", data)

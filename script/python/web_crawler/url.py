import urllib
import urllib.request

data={}
data['word']='Jecvay Notes'

url_values=urllib.parse.urlencode(data)
url="http://www.baidu.com/s?"
full_url=url+url_values

data=urllib.request.urlopen(full_url).read()
#data=data.decode('UTF-8')
#print(data)

sName = './'+'Jecvay Notes'+'.html'
with open(sName,'wb') as file:  
	file.write(data)  
file.close()
import requests
import os
import re


def parseUrlf():
    retval = 'a'
    try:
        g = int(galleryid[-1])
        if g == 1:
            g = 0
        retval = chr(ord('a') + g % 2) + retval
    except:
        pass
    return 'https://%s.hitomi.la/galleries' % retval + '/%s/%s'


galleryid = '1462305'
urlf = 'https://ltn.hitomi.la/galleries/%s.js'
print('正在获取galleryinfo...')
response = requests.get(urlf % galleryid)
galleryinfo = eval(response.text[19:-1])
print('galleryinfo已获取')

l = len(galleryinfo)
print('图像总量%d张' % l)

if not os.path.isdir(galleryid):
    os.mkdir(galleryid)
print('图片目录已创建')

urlf_pic = parseUrlf()
headers = {'Origin': 'https://hitomi.la',
           'Referer': 'https://hitomi.la/galleries/%s.html' % galleryid,
           'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36'}

c = 0
for gi in galleryinfo:
    c += 1
    if os.path.exists(galleryid + '/' + gi['name']):
        print('进度%d/%d' % (c, l), '图片%s已存在' % gi['name'])
        continue
    response = requests.get(urlf_pic % (galleryid, gi['name']), headers=headers)
    with open(galleryid + '/' + gi['name'], 'wb') as file:
        file.write(response.content)
    print('进度%d/%d' % (c, l))

import requests
import re
import os

urlss = [["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=25B6D427CCE5AD183FB81B00889E398E-1582379476311",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=FE2D8C2BD36E2C0FFE4DD808B0BAC493-1582379872719",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=366B49754EED094046497C6FA02F2D91-1614335017290",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=D51522E52AE85FE14A1FE93377544284-1582380640838",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=A193F68C2A21FB5D90331F3B75A4A0C7-1614500274556"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=47A3EF685EF76AC9BB8B8C2E860B35C5-1582900502688",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=F2BFA94D8835B966246014EEE1FE2370-1584091460560",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=AE9E46BCB54FB8EE7402C3E26109007C-1582901142017",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=8A0DDAFC51729E4699C9EA74C85AC3A6-1582901306739",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=ADBA3B4375599347E7A9ABD3D1D8EFE8-1582901407554"]]

txtss = ""
for i, urls in enumerate(urlss):
    txts = ""
    for j, url in enumerate(urls):
        response = requests.get(url)
        txt = response.content.decode('utf8')
        txt = re.sub(r"[0-9]+[\s:,]", "", txt)
        txt = re.sub(r"\s+-->\s+", "  ", txt)
        txts += "\n\n%d.%d\n\n" % (i+1, j+1)+txt
    txtss += txts
    with open(os.path.join(os.path.split(__file__)[0], '学术英语写作字幕%d.txt' % (i+1)), 'w', encoding="utf8") as f:
        f.write(txts)
with open(os.path.join(os.path.split(__file__)[0], '学术英语写作字幕合集.txt'), 'w', encoding="utf8") as f:
    f.write(txtss)

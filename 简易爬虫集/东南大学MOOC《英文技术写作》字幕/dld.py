import requests
import re
import os

urlss = [["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=1AC4C50534AA344E7363245ED08D679F-1569133935577",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=83BA0490FEA7AF7DF30B26741D0B8195-1569134028599",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=18FD356DD0A232CFEF9E226DDD8FE7AF-1569134076834",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=1F1F776124D712079D5CD5AF19A05642-1569134168298",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=2DBC8D5605609754EAEDDA031571F3DB-1569134198476",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=ADAAD34A1A65B006CC3B68A1597BDD86-1569134239754"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=414359AC7EA3A37F226B5ECF9EB4FE79-1570461222304",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=9D75CEC595F12B910F6D895341B971DA-1570464692993",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=FE9EF874C549D3C745BF04A7A0773A30-1570461807660",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=3CC211C174083AD69B49E9BD3A86560B-1570462418604"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=2DB45FA0A87661575DAA89F8864B67BD-1570994858168",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=E3EE19F68E22E77198873D34300CBA1B-1570994907579",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=F8CDA395FB7F62DB4C092CAB441ECA98-1570994948957",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=744287293457BD0D99A2AD914566A2FA-1570994975397"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=6E7448A6D1FF7D8A30B844335E0CDE3B-1573530996561",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=2B2B48987446D98EA66598D7DBB4D9D8-1573531565770",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=0A0DC477CF79B4B47638E0BB24FEE125-1573533659457",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=D07B6011F7669678565661B1A1EC9F51-1573534163741"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=5B61A167C7BED193C192D421FEB4F0FE-1572192481908",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=6D2754E79E5D445173FB5CDBD0389B6A-1572191598961",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=9468040BFB2B11AD2E0A9732FDD700E8-1572192551006",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=DF5F7E9E145B8619F66B126A2375BD08-1572192585094"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=ABAA903E494171794AD382FA77886C7A-1573658532898",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=996A770F3F6A27214726DCA4A76085BC-1572790203323",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=BC0043F5BD529807AE723950CE09FBA7-1572790264861",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=9A12CEBC0C0E309590B9FF85B87FDCA7-1572790310733"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=6E1480B5ADB7D5613679F42D06F69F1B-1573530478632",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=399F492E54B993F0F0B81DEFC42CB6DC-1574138197994",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=59137F0BEBAA4368845C73B91D66CBBA-1573529272729",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=3340CDD98838FF0CED61C68CD6F853DE-1573528709967"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=CCB38FC528FE30C9F274D16DF0774207-1573996494374",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=F0EC7086A08783573A792142AAF40644-1573996608530",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=CB9FDFDC2207DAF1B90E75D994FBB063-1573996648786",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=3F2D5AFFF4C306E3E7529093FA73C8F0-1573996712515"]]

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
    with open(os.path.join(os.path.split(__file__)[0], '英文技术写作字幕%d.txt' % (i+1)), 'w', encoding="utf8") as f:
        f.write(txts)
with open(os.path.join(os.path.split(__file__)[0], '英文技术写作字幕合集.txt'), 'w', encoding="utf8") as f:
    f.write(txtss)

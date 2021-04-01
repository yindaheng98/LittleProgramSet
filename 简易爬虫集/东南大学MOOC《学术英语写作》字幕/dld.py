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
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=ADBA3B4375599347E7A9ABD3D1D8EFE8-1582901407554"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=A415C9C1AFB7C194A41B77E289E8561F-1583416102099",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=7D1BEFAA18121C4348592F9564C761DF-1583416260444",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=BED1E9642DB8179A7B36721DA54C2EF9-1583416438804",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=D1C16F1967EE6A02D269671527FC265F-1583416661778",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=974EA85F9574B0BE45527223A4D14C83-1583416936672"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=61EC089B6283299752EF1D69BC870BA8-1584187203897",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=1487DB50B21A58027515E66F2B0A778D-1584187755025",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=BE61502E82BE80E6B9627C480797F431-1584189879760",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=8FE45735D66CF06233540E7EC237EEA0-1614335819269",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=A8B44E8F9B2A20AB1218873407742E72-1584190564787"],

         ["http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=F756A80A623A226796DEDA09856EA396-1584618823652",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=DB02B97116EFB147E6D35222BA731056-1584619022141",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=DEF9F40BCC3979D2153D1EF17F8C0B5E-1584619222684",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=EAF37670CCFBCC6A8B62654C968BA7CF-1584619490549",
          "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=E165760666D951033554FC7E2194B8C4-1584461674207"]]

txtss = ""
for i, urls in enumerate(urlss):
    txts = ""
    for j, url in enumerate(urls):
        response = requests.get(url)
        txt = response.content.decode('utf8')
        txt = re.sub(r"[0-9]+[\s:,]", "", txt)
        txt = re.sub(r"\s+-->\s+", "\n", txt)
        txts += "\n\n%d.%d\n\n" % (i+1, j+1)+txt
    txtss += txts
    with open(os.path.join(os.path.split(__file__)[0], '学术英语写作字幕%d.txt' % (i+1)), 'w', encoding="utf8") as f:
        f.write(txts)
with open(os.path.join(os.path.split(__file__)[0], '学术英语写作字幕合集.txt'), 'w', encoding="utf8") as f:
    f.write(txtss)

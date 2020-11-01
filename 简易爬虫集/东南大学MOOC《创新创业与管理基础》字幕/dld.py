import requests
import re
import os

urls = [
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=327A381D53ACE9CA528429F79F538AE4-1567215531993",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=433DFCD984FE4F901EB04959EA958466-1567236740344",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=66C9DF98F748C2572DFB4D846313FFDA-1567216961466",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=4C3AB7D42F32CEC526FD247117FEC5C9-1567217194336",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=AE35CEDE16C0D10EA635E05BC876CB35-1567217269846",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=9CD893ECC83FE6DBB23226F27D4F3ABB-1567234495125",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=847ADAAA20F5642C21C4DF73E2ACE3F0-1573959820960",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=FBA269EC8318753F8B158C6F19C91E22-1567217779013",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=6B9351570ED82ECE10AB26D07AE30DCD-1567219165954",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=115CC0FD7ED1DA1093E97C27079F5A3C-1567219608330",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=23898482BAF2BE0160F030EA03DF296F-1567236840132",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=6D6D2FC1F8344644F81AF7D958675AE5-1567236954390",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=1A6B62C0E0CD4E48808E686492BBDBFF-1567218549874",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=5B64977DE56E29F80B0ADF53F0C18E9D-1567237389344",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=86E36D69A5796672F99C2715C42D669D-1567220753854",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=9DB395372BA76899C7207B59EC077F6F-1567221259201",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=210AFA71757BFDE372C1C4D74808A40D-1567235192856",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=D77EC30F75C68E1603E2BCBC4C2ADF2C-1567235385204",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=59891F2B0B953474B17BCE713C65869F-1567221480610",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=60FD251F241F6E10CB4349CADD4A0FB8-1567235481922",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=0CEE4AE7D23964EF1BAB83CCC88F211E-1567221847660",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=B40C841FE0BEA18150EC2FFDB7947988-1567235592259",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=04DCC1285BFC058EA824274A25253882-1567235676507",
    "http://www.icourse163.org/video/downloadVideoSrt.htm?srcKey=5413B8B678BCFFD164495A76A6F98D07-1567222047019"
]

i = 1
txts = ""
for url in urls:
    response = requests.get(url)
    txt = response.content.decode('utf8')
    txt = re.sub(r"[0-9]+[\s:,]", "", txt)
    txt = re.sub(r"\s+-->\s+", "  ", txt)
    txts += "\n\n第%d课\n\n" % i+txt
    i += 1
with open(os.path.join(os.path.split(__file__)[0], '创新创业与管理基础字幕合集.txt'),'w',encoding="utf8") as f:
    f.write(txts)
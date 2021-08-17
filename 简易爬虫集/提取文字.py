import subprocess
from config import *

vert_imname_res = [
    re.compile(r'cm[em][0-9]+$'),
    re.compile(r'knk[clq][0-9]+$'),
    re.compile(r'nk2[cj][0-9]+$'),
    re.compile(r'ssk[ikno][0-9]+$'),
    re.compile(r'zps[efim][0-9]+$'), ]  # 哪些文件是横向文字

for k, v in dict_image.items():
    language = 'jpn'
    for vert_imname_re in vert_imname_res:
        if vert_imname_re.match(k) != None:
            language = 'jpn_vert'
            break
    impath = dst_impath_fmt(k)
    cmd = ['tesseract', impath, 'stdout', '-l', language, '--oem', '3']
    p = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    txt = ''
    for line in p.stdout:
        s = line.decode().strip().replace(' ', '')
        txt = txt + s + "\n"
        print(k, '>>>', s)
    txtpath = impath + '.txt'
    with open(txtpath, 'w') as f:
        f.write(txt)

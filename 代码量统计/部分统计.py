import re
from 统计程序文件 import flines

pt = r'ExprtField\\Data'
typelines = {}

for ftype in flines:
    typelines[ftype] = 0
    for finfo in flines[ftype]:
        if(re.search(pt, finfo[1]) != None):
            typelines[ftype] += finfo[0]

print(typelines)

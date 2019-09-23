from 统计程序文件 import flines

typelines = {}

for ftype in flines:
    typelines[ftype] = 0
    for finfo in flines[ftype]:
        typelines[ftype] += finfo[0]

print(typelines)

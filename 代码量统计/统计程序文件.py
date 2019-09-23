from 查找程序文件 import files


def count_lines(path):
    c = 0
    try:
        f = open(path, 'r', encoding='UTF-8')
        for l in f.readlines():
            if(len(l) >= 3):
                c += 1
    except:
        f = open(path, 'r', encoding='gbk')
        for l in f.readlines():
            if(len(l) > 0):
                c += 1
    f.close()
    return c


flines = {ftype: [] for ftype in files}

fls = {i: [] for i in range(10000)}

for ftype in files:
    for f in files[ftype]:
        c = count_lines(f)
        fls[c].append(f)
        flines[ftype].append((c, f))

with open('统计结果.txt', 'w') as f:
    for i in fls:
        for fp in fls[i]:
            f.writelines(str(i)+'\t:\t'+fp+'\n')

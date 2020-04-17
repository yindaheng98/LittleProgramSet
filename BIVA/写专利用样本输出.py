import numpy as np
from NameConf import units
from GetData import names, sexes, calculate_data, get_data_from_csv
from 回归分析结果 import params


def pick_data(df, ps):
    """数据筛选"""
    for name in ps:
        p = ps[name]
        if p is None:
            continue
        XX = np.array([df['R/H'], df['Xc/H'], df['Rsp'], df['Xcsp']])
        df['%s(%s)' % (name, units[name])] = np.matmul(np.array(p)[0:-1], XX) + p[-1]
    return df


data = {}
for name in names:
    d = {}
    for sex in sexes:
        ps = params[sex]
        d[sex] = get_data_from_csv(name, sex)
        d[sex] = calculate_data(d[sex])
        d[sex] = pick_data(d[sex], ps)
    data[name] = d

data[names[3]][sexes[0]].to_csv("专利用数据" + sexes[0] + '（表中“结果”为' + names[3] + '实际值）.csv', index=False, encoding='ANSI')
data[names[3]][sexes[1]].to_csv("专利用数据" + sexes[1] + '（表中“结果”为' + names[3] + '实际值）.csv', index=False, encoding='ANSI')
print(data)

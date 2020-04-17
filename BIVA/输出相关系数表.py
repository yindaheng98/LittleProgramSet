import numpy as np

from NameConf import translations, names
from 一元回归分析 import data


def construct_str(param, pvalue):
    if pvalue < 0.01:
        return '%.1f$^{**}$' % param
    elif pvalue < 0.05:
        return '%.1f$^{*}$' % param
    else:
        return '%.1f' % param


def process(COMP, SEX):
    d = data[COMP][SEX]
    (corrs, pvalues) = np.array([d[i]['相关系数'] for i in ['RH', 'XH', 'Rsp', 'Xsp']]).T
    res_str = []
    res_str.extend([construct_str(param, pvalue) for param, pvalue in zip(corrs, pvalues)])
    return res_str


for name in names:
    dat = [translations[name]]
    dat.extend(process(name, '男'))
    dat.extend(process(name, '女'))
    print('%s&%s&%s&%s&%s&%s&%s&%s&%s\\\\' % tuple(dat))

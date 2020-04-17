from NameConf import translations, units, names
from 数据连接 import SQLf as SQLf_combine
from G.connection import connection

import numpy as np
import scipy.stats as stats

chamical_total = {'男': 0, '女': 0}


def get_chamical(COMP):
    data = []
    for SEX in ['男', '女']:
        cursor = connection.cursor()
        SQLf = "SELECT 结果 FROM(%s) AS T"
        SQL = SQLf % (SQLf_combine % (COMP, SEX))
        cursor.execute(SQL)
        data.append(np.array(cursor.fetchall()).T[0])
    t = stats.ttest_ind(data[0], data[1])
    chamical_total['男'] += data[0].size
    chamical_total['女'] += data[1].size
    return data[0].size, \
           np.mean(data[0]), \
           np.std(data[0]), \
           data[1].size, \
           np.mean(data[1]), \
           np.std(data[1]), \
           t.statistic, \
           t.pvalue


eCOMPs = {'Age': "SELECT AVG(ROUND(abs(TIMESTAMPDIFF(DAY, 出生日期, 检测日期))/365)) FROM bcm原始数据 WHERE 性别='%s' GROUP BY 姓名",
          'Height': "SELECT AVG(身高) FROM bcm原始数据 WHERE 性别='%s' GROUP BY 姓名",
          'Weight': "SELECT AVG(体重) FROM bcm原始数据 WHERE 性别='%s' GROUP BY 姓名",
          'BMI': "SELECT AVG(体重*10000/(身高*身高)) FROM bcm原始数据 WHERE 性别='%s' GROUP BY 姓名",
          'R': "SELECT Z*COS(Phi*PI()/180) FROM bcm原始数据 WHERE 性别='%s'",
          'Xc': "SELECT Z*SIN(Phi*PI()/180) FROM bcm原始数据 WHERE 性别='%s'",
          'R/H': "SELECT Z*COS(Phi*PI()/180)*100/身高 FROM bcm原始数据 WHERE 性别='%s'",
          'Xc/H': "SELECT Z*SIN(Phi*PI()/180)*100/身高 FROM bcm原始数据 WHERE 性别='%s'",
          'Rsp': "SELECT Z*COS(Phi*PI()/180)*体重*10000/(身高*身高) FROM bcm原始数据 WHERE 性别='%s'",
          'Xcsp': "SELECT Z*SIN(Phi*PI()/180)*体重*10000/(身高*身高) FROM bcm原始数据 WHERE 性别='%s'"}

eunits = {'Age': "y",
          'Height': "cm",
          'Weight': "kg",
          'BMI': "kg/m$^2$",
          'R': "Ohm",
          'Xc': "Ohm",
          'R/H': "Ohm/m",
          'Xc/H': "Ohm/m",
          'Rsp': "Ohm$\\cdot$m$^2$/kg",
          'Xcsp': "Ohm$\\cdot$m$^2$/kg"}


def get_electrical(COMP):
    data = []
    for SEX in ['男', '女']:
        cursor = connection.cursor()
        cursor.execute(eCOMPs[COMP] % SEX)
        data.append(np.array(cursor.fetchall()).T[0].astype(float))
    t = stats.ttest_ind(data[0], data[1])
    return np.mean(data[0]), np.std(data[0]), np.mean(data[1]), np.std(data[1]), t.statistic, t.pvalue


if __name__ == '__main__':
    for COMP in eCOMPs:
        t = [COMP, eunits[COMP]]
        t.extend(get_electrical(COMP))
        print('%s(%s)&%.1f&%.1f&%.1f&%.1f&%.1f&%.3f\\\\' % tuple(t))
    for COMP in names:
        t = [translations[COMP], units[COMP]]
        t.extend(get_chamical(COMP))
        print('%s(%s)&%d&%.1f&%.1f&%d&%.1f&%.1f&%.1f&%.3f\\\\' % tuple(t))
    print('Combined 数据量 男:%d,女:%d' % (chamical_total['男'], chamical_total['女']))

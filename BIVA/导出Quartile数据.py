import numpy as np
from GetData import data

percent = 0.05
data_path = 'Quartile数据/'


def process_quartile(name, sex):
    RcH, XcH, Rsp, Xsp, r = data[name][sex]
    arg = np.argsort(r)
    n = int(len(arg) * percent)
    print(name, sex, '上下各', n)
    VHmax = np.array([RcH, XcH]).T[arg[0:n]]
    VHmin = np.array([RcH, XcH]).T[arg[-n:]]
    np.savetxt(data_path + '%s-%s-Classic-max.csv' % (name, sex), VHmax, fmt='%f', delimiter=',')
    np.savetxt(data_path + '%s-%s-Classic-min.csv' % (name, sex), VHmin, fmt='%f', delimiter=',')
    Vspmax = np.array([Rsp, Xsp]).T[arg[0:n]]
    Vspmin = np.array([Rsp, Xsp]).T[arg[-n:]]
    np.savetxt(data_path + '%s-%s-Specific-max.csv' % (name, sex), Vspmax, fmt='%f', delimiter=',')
    np.savetxt(data_path + '%s-%s-Specific-min.csv' % (name, sex), Vspmin, fmt='%f', delimiter=',')


for name in data:
    for sex in data[name]:
        process_quartile(name, sex)
np.savetxt(data_path + 'names.csv', np.array(list(data)), fmt='%s', delimiter=',')

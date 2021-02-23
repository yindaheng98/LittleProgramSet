import json

import matplotlib.pyplot as plt
import matplotlib.colors as mcolors
from N import N

plt.rcParams['font.sans-serif'] = ['SimHei']
result = {}
with open('./result.%d.json' % N, "r", encoding='UTF-8') as f:
    result = json.load(f)

N = result['N']
rho_list = result['rho_list']
n_list = result['n_list']
result = result['result']

names = {
    'MMn': '$M|M|n$队列',
    'nMM1': '概率分裂的$n$个$M|M|1$队列',
    'nEnM1': '$n$个$En|M|n$队列',
    'nMM1Short': '顾客选择最短队列的$n$个$M|M|1$队列',
    'simulate': '仿真值',
    'theory': '理论值'
}

colors = {
    'MMn': list(mcolors.TABLEAU_COLORS)[0],
    'nMM1': list(mcolors.TABLEAU_COLORS)[1],
    'nEnM1': list(mcolors.TABLEAU_COLORS)[2],
    'nMM1Short': list(mcolors.TABLEAU_COLORS)[3],
}

x = rho_list
for n in result:
    data = result[n]
    fname = 'figure/n=%s的所有队列.png' % n
    print(fname)
    plt.figure(figsize=(13, 12))
    for model in data:
        label_pre = names[model]
        for mod in data[model]:
            label_suf = names[mod]
            label = label_pre + ' - ' + label_suf
            y = data[model][mod]
            print(label, y)
            if mod == 'theory':
                plt.plot(x, y, label=label, color=colors[model], linestyle='--')
            else:
                plt.plot(x, y, label=label, color=colors[model])
    plt.xlabel(r'$\frac{\lambda}{n\mu}$', fontsize=30)
    plt.ylabel(r'$Elq$', fontsize=30)
    plt.legend(fontsize=15)
    plt.savefig(fname)

colors_n = {str(i + 1): c for i, c in enumerate(list(mcolors.TABLEAU_COLORS))}
for model in colors:
    fname = 'figure/%s.png' % names[model].replace('$', "").replace('|', "")
    print(fname)
    plt.figure(figsize=(13, 12))
    for n in result:
        label_pre = '$n=$%2s' % n
        for mod in result[n][model]:
            label_suf = names[mod]
            label = label_pre + ' - ' + label_suf
            y = result[n][model][mod]
            print(label, y)
            if mod == 'theory':
                plt.plot(x, y, label=label, color=colors_n[n], linestyle='--')
            else:
                plt.plot(x, y, label=label, color=colors_n[n])
    plt.xlabel(r'$\frac{\lambda}{n\mu}$', fontsize=30)
    plt.ylabel(r'$Elq$', fontsize=30)
    plt.legend(fontsize=15)
    plt.savefig(fname)

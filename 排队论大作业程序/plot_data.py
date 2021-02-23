import json

import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
N = 300
result = {}
with open('./result.%d.json' % N, "r", encoding='UTF-8') as f:
    result = json.load(f)

N = result['N']
rho_list = result['rho_list']
n_list = result['n_list']
result = result['result']

names = {
    'MMn': 'M|M|n 队列',
    'nMM1': '概率分裂的 n 个 M|M|1 队列',
    'nEnM1': 'n 个 En|M|n 队列',
    'nMM1Short': '顾客选择最短队列的 n 个 M|M|1 队列',
    'simulate': '仿真值',
    'theory': '理论值'
}

colors = {
    'MMn': 'cornflowerblue',
    'nMM1': 'chocolate',
    'nEnM1': 'forestgreen',
    'nMM1Short': 'hotpink',
}

x = rho_list
for n in result:
    data = result[n]
    fname = 'figure/n=%s.png' % n
    print(fname)
    plt.figure()
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
    plt.xlabel(r'$\frac{\lambda}{n\mu}$')
    plt.ylabel(r'$Elq$')
    plt.legend()
    plt.savefig(fname)

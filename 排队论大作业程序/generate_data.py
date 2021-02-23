import numpy as np
import json
from MMnSimulator import MMnSimulator
from nMM1Simulator import nMM1Simulator
from nEnM1Simulator import nEnM1Simulator
from nMM1ShortSimulator import nMM1ShortSimulator
from N import N

rho_list = list(np.arange(0.1, 1., 0.05))
n_list = list(range(1, 11))
result = {
    'N': N,
    'rho_list': rho_list,
    'n_list': n_list,
    'result': {},
}

miu = 1
for n in n_list:
    data = {
        'MMn': {'simulate': [], 'theory': []},
        'nMM1': {'simulate': [], 'theory': []},
        'nEnM1': {'simulate': [], 'theory': []},
        'nMM1Short': {'simulate': []},
    }
    for rho in rho_list:
        _miu = miu
        _lambda = rho * _miu * n
        for name in data:
            simulator = eval(name + "Simulator(_lambda, _miu, n)")
            if not name == 'nMM1Short':
                data[name]['theory'].append(simulator.Elq_theory)
            data[name]['simulate'].append(simulator.run(N))
    result['result'][n] = data
with open('./result.%d.json' % N, "w", encoding='UTF-8') as f:
    json.dump(result, f, indent=4)

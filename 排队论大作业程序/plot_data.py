import json

import matplotlib.pyplot as plt

N = 300
result = {}
with open('./result.%d.json' % N, "r", encoding='UTF-8') as f:
    result = json.load(f)

N = result['N']
factor_list = result['factor_list']
n_list = result['n_list']
result = result['result']

print(N)
print(factor_list)
print(n_list)
print(result)

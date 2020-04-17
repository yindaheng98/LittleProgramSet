import json
from NameConf import names, sexes, translations


def construct_str(param, pvalue):
    if pvalue < 0.01:
        return '%.3f$^{**}$' % param
    elif pvalue < 0.05:
        return '%.3f$^{*}$' % param
    else:
        return '%.3f' % param


data = json.load(open('结果/Quartile结果.json', 'r', encoding='utf-8'))
results = ''
for name in names:
    results += translations[name] + '&'
    for sex in sexes:
        for typ in ['Classic', 'Specific']:
            index = '%s-%s-%s' % (name, sex, typ)
            if index in data:
                d = data[index]
                results += construct_str(d[0], d[1]) + '&'
            else:
                results += '-&'
    results = results[0:-1] + '\\\\\n'
print(results)

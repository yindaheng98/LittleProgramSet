from 多元回归分析 import data as multi_data
from 一元回归分析 import data as singl_data
from NameConf import names, sexes, translations, units

wanted_error = 'F'
'''
print('\t\t多元回归均方误差\t一元回归相对误差(R/H)\t一元回归相对误差(Xc/H)\t一元回归相对误差(Rsp)\t一元回归相对误差(Xcsp)')
for name in names:
    for sex in sexes:
        result = [multi_data[name][sex][wanted_error],
                  [singl_data[name][sex][r][wanted_error] for r in ['RH', 'XH', 'Rsp', 'Xsp']]]
        print('%s\t%s\t%f\t%s' % (name, sex, result[0], ('%f\t%f\t%f\t%f' % tuple(result[1]))))
'''


def float_to_str(n):
    k = 0
    nn = n
    while abs(nn) < 1:
        nn *= 10
        k += 1
    if k >= 4:
        return '%.3f$\\times 10^{-%d}$' % (nn, k)
    return '%.3f' % n


def construct_str(param, pvalue):
    param = float_to_str(param)
    if pvalue < 0.01:
        return '%s$^{**}$' % param
    elif pvalue < 0.05:
        return '%s$^{*}$' % param
    else:
        return '%s' % param


'''
def construct_str(param, pvalue):
    param = float_to_str(param)
    if pvalue < 0.01:
        return '%s**' % param
    elif pvalue < 0.05:
        return '%s*' % param
    else:
        return '%s' % param
'''

wanted_sig = 'F-pvalue'
results = ''
sex = sexes[1]
for name in names:
    results += '%s' % (translations[name])
    dd = multi_data[name][sex]
    sdd = singl_data[name][sex]
    d = tuple(construct_str(sdd[r][wanted_error], sdd[r][wanted_sig]) for r in ['RH', 'XH', 'Rsp', 'Xsp']) + \
        tuple((construct_str(dd["All"][wanted_error], dd["All"][wanted_sig]),)) + \
        tuple((construct_str(dd["Classic"][wanted_error], dd["Classic"][wanted_sig]),)) + \
        tuple((construct_str(dd["Specific"][wanted_error], dd["Specific"][wanted_sig]),))
    results += '&%s&%s&%s&%s&%s&%s&%s' % d
    results += '\\\\\n'
    # results += '\t%s\t%s\t%s\t%s\t%s\t%s\t%s' % d
    # results += '\n'

print(results)


def float_to_str1(n):
    k = 0
    nn = n
    while abs(nn) < 1:
        nn *= 10
        k += 1
    if k >= 3:
        return '%+.6f' % n
    return '%+.4f' % n


def construct_eq(data, typ):
    if data["F-pvalue"] > 0.01:
        return "显著性不达标"
    s = "y="
    d = tuple(float_to_str1(n) for n in data["回归系数"]) + (float_to_str1(data["截距"]),)
    if typ == 'All':
        s += "%s R1%s X1%s R2%s X2%s" % d
    elif typ == 'Classic':
        s += "%s R1%s X1%s" % d
    elif typ == 'Specific':
        s += "%s R2%s X2%s" % d
    else:
        s += ("%s " + {'RH': 'R1', 'XH': 'X1', 'Rsp': 'R2', 'Xsp': 'X2'}[typ] + "%s") % d
    return s


def construct_pa(data, typ):
    if data["F-pvalue"] > 0.01:
        return None
    k = tuple(data["回归系数"])
    b = (data["截距"],)
    if typ == 'All':
        return k + b
    elif typ == 'Classic':
        return k + (0, 0) + b
    elif typ == 'Specific':
        return (0, 0) + k + b
    else:
        kk = [0, 0, 0, 0]
        kk[{'RH': 0, 'XH': 1, 'Rsp': 2, 'Xsp': 3}[typ]] = k[0]
        return tuple(kk) + b


equations = {}
params = {}
for sex in sexes:
    equations[sex] = {}
    params[sex] = {}
    for name in names:
        dd = multi_data[name][sex]
        sdd = singl_data[name][sex]

        dde = {k: dd[k][wanted_error] for k in dd if k in ["All", "Classic", "Specific"]}
        sdde = {r: sdd[r][wanted_error] for r in ['RH', 'XH', 'Rsp', 'Xsp']}

        ddem = max(dde, key=dde.get)
        sddem = max(sdde, key=sdde.get)

        typ = ddem if dd[ddem][wanted_error] > sdd[sddem][wanted_error] else sddem
        data = dd[ddem] if dd[ddem][wanted_error] > sdd[sddem][wanted_error] else sdd[sddem]

        m = construct_eq(data, typ)
        p = construct_pa(data, typ)
        equations[sex][name] = m
        params[sex][name] = p

for sex in sexes:
    eq_results = ''
    print(sex)
    for name in names:
        eq_results += "%s(%s)\t%s\n" % (name, units[name], equations[sex][name])
    print(eq_results)

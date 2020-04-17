import numpy as np
from BIVA2 import lin_regression


# 绘制线性回归线
def plot_lin(ax, X, y, rx, ry, c, marker, color, linestyles=None):
    scatter = ax.scatter(X, y, c=c, marker=marker, edgecolors=color, s=10, linewidths=0.1)
    k, b, r_value, p_value, std_err = lin_regression(X, y)
    line = ax.plot(rx, k * np.array(rx) + b, color='black', linestyle=linestyles, linewidth=0.5)[0]
    return line, scatter, (k, b), (r_value, p_value)


def _plot_lin_constructor(com_str, legend_elements, legend_str, SEX, line, scatter, k, b, r_value, p_value):
    com_str += '  %s:r=%.3f\n  (p=%.3f)\n' % (SEX, r_value, p_value)
    legend_elements.extend([scatter, line])
    legend_str.extend([SEX, 'k=%9.2e\nb=%9.2e' % (k, b)])
    return com_str, legend_elements, legend_str


def plot_lin_all(ax, X, y, rx, ry):
    com_str = ''
    legend_elements = []
    legend_str = []
    out_d = {}

    SEX = 'Men'
    line, scatter, (k, b), (r_value, p_value) = plot_lin(ax, X['男'], y['男'], rx, ry,
                                                         c='', color='k', marker='.', linestyles='dashdot')
    out_d[SEX] = (r_value, p_value)
    com_str, legend_elements, legend_str = _plot_lin_constructor(
        com_str, legend_elements, legend_str, SEX, line, scatter, k, b, r_value, p_value)

    SEX = 'Women'
    line, scatter, (k, b), (r_value, p_value) = plot_lin(ax, X['女'], y['女'], rx, ry,
                                                         c='k', color='', marker='.', linestyles='solid')
    out_d[SEX] = (r_value, p_value)
    com_str, legend_elements, legend_str = _plot_lin_constructor(
        com_str, legend_elements, legend_str, SEX, line, scatter, k, b, r_value, p_value)

    ax.set_xlim(rx)
    ax.set_ylim(ry)
    ax.text(rx[1] - (rx[1] - rx[0]) * 0.3, ry[0], com_str)
    ax.legend(legend_elements, legend_str, loc='upper left')
    return out_d


rxs = {
    'RH': [0, 600],
    'Rsp': [0, 20000],
    'XH': [0, 60],
    'Xsp': [0, 2000]
}

xlabels = {
    'RH': 'R/H(Ohm/m)',
    'Rsp': r'Rsp(Ohm$\cdot$kg/m$^2$)',
    'XH': 'Xc/H(Ohm/m)',
    'Xsp': r'Xcsp(Ohm$\cdot$kg/m$^2$)'
}

img_path = '线性回归图/'

if __name__ == "__main__":
    import matplotlib.pyplot as plt
    from BIVA2 import get_data, pick_data, translations, units
    from BIVA2 import translations_file
    from AnalyseData import argselect_quartile_min,argselect_quartile_max

    out_data = {}


    def plot_comp(COMP):
        RH, XH, Rsp, Xsp, r = {}, {}, {}, {}, {}

        for SEX in ['男', '女']:
            DATA = get_data(COMP, SEX)
            RH[SEX], XH[SEX], Rsp[SEX], Xsp[SEX], r[SEX] = pick_data(DATA)

        out_d = {}
        for x in rxs:
            fig = plt.figure(figsize=(4, 3), dpi=300)

            ax = fig.add_subplot(111)
            y = np.concatenate(list(r.values()))
            
            ry_minr=argselect_quartile_min(y, 0.01)
            ry_min=max(y[ry_minr]) if len(ry_minr)>0 else min(y)
            ry_maxr=argselect_quartile_max(y, 0.01)
            ry_max=min(y[ry_maxr]) if len(ry_maxr)>0 else max(y)
            ry = [ry_min, ry_max]
            
            # ry = [min(y), max(y)]
            
            out_d[x] = plot_lin_all(ax, eval(x), r, rxs[x], ry)
            ax.set_xlabel(xlabels[x])
            ax.set_ylabel('%s(%s)' % (translations[COMP], units[COMP]))

            plt.tight_layout()
            plt.savefig(img_path + '%s-%s.pdf' % (''.join(translations_file[COMP].split(' ')), x))
            plt.close()
        out_data[COMP] = out_d


    def print_out(COMP):
        out_str = '%s (' % translations[COMP]
        for SEX in ['Men', 'Women']:
            out_str += 'In %s, ' % {'Men': 'men', 'Women': 'women'}[SEX]
            for v, i in zip(['RH', 'XH', 'Rsp', 'Xsp'], ['R/H', 'Xc/H', 'Rcsp', 'Xcsp']):
                out_str += '%s: r = %.3f, ' % (i, out_data[COMP][v][SEX][0])
                p = out_data[COMP][v][SEX][1]
                out_str += 'p %s; ' % ('< 0.001' if p < 0.001 else ('= %.3f' % p))
        out_str = out_str[0:-2] + ')'
        print(out_str)


    plt.rcParams['font.sans-serif'] = ['SimHei']
    plt.rcParams['font.size'] = 8

    from BIVA2 import COMPs

    for COMP in COMPs:
        plot_comp(COMP)
        print_out(COMP)

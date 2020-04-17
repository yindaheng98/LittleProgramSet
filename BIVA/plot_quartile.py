import numpy as np
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['font.size'] = 8

from BIVA2 import translations_file
from BIVA2 import get_data, pick_data
from BIVA2 import multivariate_normal_BIVA


# 在平面上绘制二元变量的95%的正态分布置信区间（正态分布以XY均值方差协方差算出）
def plot_normal_contour95(ax, X, Y, n, linestyles=None):
    Xmax, Xmin, Ymax, Ymin = max(X), min(X), max(Y), min(Y)
    Xscale, Yscale = (Xmax - Xmin), (Ymax - Ymin)
    XH = np.linspace(Xmin - Xscale * 2, Xmax + Xscale * 2, n * 5)
    YH = np.linspace(Ymin - Yscale * 2, Ymax + Yscale * 2, n * 5)
    rh, xh = np.meshgrid(XH, YH)
    pos = np.dstack((rh, xh))
    rv = multivariate_normal_BIVA(X, Y)
    (x, y) = (np.mean(X) - 2 * np.std(X), np.mean(Y) - 2 * np.std(Y))  # 一维的三西格玛法则扩展到二维
    thr = rv.pdf(np.dstack(np.meshgrid([x], [y])))
    ax.contour(XH, YH, rv.pdf(pos), 0, colors='black', levels=[thr], linestyles=linestyles, linewidths=0.5)
    return ax.plot([], [], color='black', linestyle=linestyles, linewidth=0.5)[0]


# 将95%的正态分布置信区间同散点图一同绘制
def plot_scatter_contour95(ax, R, X, c='', color=None, marker=None, linestyles=None):
    scatter = ax.scatter(R, X, c=c, marker=marker, edgecolors=color)
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.spines['bottom'].set_position(('data', 0))
    ax.spines['left'].set_position(('data', 0))
    return [scatter, plot_normal_contour95(ax, R, X, 100, linestyles=linestyles)]


from BIVA2 import argselect_quartile_max, argselect_quartile_min


# 绘制上下percent的数据的95%的正态分布置信区间和散点图
def plot_quartile(ax, R, X, r, percent):
    legend = []
    arg = argselect_quartile_min(r, percent)
    Q3 = plot_scatter_contour95(ax, R[arg], X[arg], c='', color='k', marker='o', linestyles='dashdot')
    legend.extend(['<Q1', ''])
    arg = argselect_quartile_max(r, percent)
    Q1 = plot_scatter_contour95(ax, R[arg], X[arg], c='k', color='', marker='o', linestyles='solid')
    legend.extend(['>Q3', ''])
    ax.legend([Q1[0], Q1[1], Q3[0], Q3[1]], legend, loc='upper left')


from BIVA2 import percent


# 画上下5%quartile的数据
def plot_quartile95(ax, R, X, r, rx, ry):
    plot_quartile(ax, R, X, r, percent)
    ax.set_xlim(rx)
    ax.set_ylim(ry)


# 画所有数据
def plot_all(ax, R, X, rx, ry):
    plot_scatter_contour95(ax, R, X)
    ax.set_xlim(rx)
    ax.set_ylim(ry)


def plot_Ttest(ax, T, P):
    ax.text(0, 0, ('  ' + r'T$^2$=%.1f' + '\n  p=%.3f\n') % (T, P))


import json

results = json.load(open('结果/Quartile结果.json', 'r', encoding='utf-8'))

img_dir = '层次分析图/'


def process_Classic(ax, RH, XH, r):
    print(COMP + '-' + SEX + '-Classic')
    ax.set_xlabel('R/H(Ohm/m)')
    ax.set_ylabel('Xc/H(Ohm/m)')
    plot_quartile95(ax, RH, XH, r, rx=[0, 600], ry=[0, 60])
    T, P = results['%s-%s-Classic' % (COMP, SEX)]
    plot_Ttest(ax, T, P)


def process_Specific(ax, Rsp, Xsp, r):
    print(COMP + '-' + SEX + '-Specific')
    ax.set_xlabel(r'Rsp(Ohm$\cdot$kg/m$^2$)')
    ax.set_ylabel(r'Xcsp(Ohm$\cdot$kg/m$^2$)')
    plot_quartile95(ax, Rsp, Xsp, r, rx=[0, 20000], ry=[0, 2000])
    T, P = results['%s-%s-Specific' % (COMP, SEX)]
    plot_Ttest(ax, T, P)


def process(COMP, SEX):
    DATA = get_data(COMP, SEX)
    RH, XH, Rsp, Xsp, r = pick_data(DATA)
    info = ''.join(translations_file[COMP].split(' ')) + '-' + {'男': 'man', '女': 'woman'}[SEX]

    try:
        fig = plt.figure(figsize=(4, 3), dpi=300)
        ax = fig.add_subplot(111)
        process_Classic(ax, RH, XH, r)
        plt.tight_layout()
        plt.savefig(img_dir + info + '-Classic' + '.pdf')
    except:
        pass

    try:
        fig = plt.figure(figsize=(4, 3), dpi=300)
        ax = fig.add_subplot(111)
        process_Specific(ax, Rsp, Xsp, r)
        plt.tight_layout()
        plt.savefig(img_dir + info + '-Specific' + '.pdf')
    except:
        pass


if __name__ == '__main__':
    from BIVA2 import translations, units, COMPs

    for COMP in COMPs:
        for SEX in ['男', '女']:
            try:
                process(COMP, SEX)
            except:
                pass

from GetData import data, names, sexes

import numpy as np
from 一元回归分析 import ols_summary

ddd = {}

for name in names:
    dd = {s: {} for s in sexes}
    for sex in sexes:
        X = np.array(data[name][sex][0:4]).T
        y = data[name][sex][4]
        dd[sex]["All"] = ols_summary(X, y)
        dd[sex]["Classic"] = ols_summary(X[:, 0:2], y)
        dd[sex]["Specific"] = ols_summary(X[:, 2:4], y)
        dd[sex]["R"] = ols_summary(X[:, 0:4:2], y)
        dd[sex]["X"] = ols_summary(X[:, 1:4:2], y)
    ddd[name] = dd

data = ddd

if __name__ == "__main__":
    print(data)

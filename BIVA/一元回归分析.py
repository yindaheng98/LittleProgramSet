from scipy.stats.stats import pearsonr
from scipy.stats import stats

from NameConf import names, sexes
from GetData import data
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error, r2_score
import numpy as np
import math

import statsmodels.api as sm


def ols_summary(X, y):
    model = LinearRegression()
    model.fit(X, y)
    y_pred = model.predict(X)

    ols = sm.OLS(y, np.concatenate((np.ones((X.shape[0], 1)), X), 1))
    result = ols.fit()
    result.summary()
    return {
        '截距': result.params[0],
        '回归系数': result.params[1:],
        '截距pvalue': result.pvalues[0],
        'pvalues': result.pvalues[1:],
        'R': math.sqrt(result.rsquared),
        'RMSE': np.sqrt(mean_squared_error(y, y_pred)),
        "MAPE": np.mean(np.abs(y - y_pred) / y),
        'F': result.fvalue,
        'F-pvalue': result.f_pvalue
    }


ddd = {}

for name in names:
    d = {}
    for sex in sexes:
        dd = {}
        RH, XH, Rsp, Xsp, r = data[name][sex]
        for v in ['RH', 'XH', 'Rsp', 'Xsp']:
            vv = eval(v)
            (corrs, pvalues) = pearsonr(vv, r)
            slope, intercept, r_value, p_value, std_err = stats.linregress(vv, r)
            vv = vv.reshape(-1, 1)
            summary = ols_summary(vv, r)
            summary["相关分析"] = (corrs, pvalues)
            dd[v] = summary
        d[sex] = dd
    ddd[name] = d

data = ddd

if __name__ == "__main__":
    print(ddd)

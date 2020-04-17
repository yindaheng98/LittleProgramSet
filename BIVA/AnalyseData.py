import numpy as np
from scipy.stats import multivariate_normal


def multivariate_normal_BIVA(R, X):
    return multivariate_normal(np.mean([R, X], axis=1), np.cov(R, X))


def argselect_quartile_min(r, percent, order=None):
    """升序排序并取最小的前percent的数据的序号"""
    if percent > 1 or percent <= 0:
        raise Exception("percent需满足0<percent<=1")
    return np.argsort(r, order=order)[0:int(len(r) * percent)]


def argselect_quartile_max(r, percent, order=None):
    """选取最大的前percent的数据"""
    if percent > 1 or percent <= 0:
        raise Exception("percent需满足0<percent<=1")
    if int(len(r) * percent) <= 0:
        return []
    return np.argsort(r, order=order)[-int(len(r) * percent):]


from scipy.stats import stats


def lin_regression(X, y):
    slope, intercept, r_value, p_value, std_err = stats.linregress(X, y)
    return slope, intercept, r_value, p_value, std_err

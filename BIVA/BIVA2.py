import pandas as pd
import numpy as np

from 数据连接 import data_dir, SQLf, SQL_to_pandas

drop_range = 0.05


def get_data(COMP, SEX):
    return get_data_from_csv(COMP, SEX)


def get_data_from_database(connection, COMP, SEX):
    cursor = connection.cursor()
    cursor.execute(SQLf % (COMP, SEX))
    data = SQL_to_pandas(cursor)
    cursor.close()
    return calculate_data(data)


def get_data_from_csv(COMP, SEX):
    data = pd.read_csv(data_dir + COMP + '-' + SEX + '.csv', encoding='utf8', engine='python')
    return calculate_data(data)


def calculate_data(data):
    data['R'] = data['Z'] * np.cos(data['Phi'] * np.pi / 180)
    data['Xc'] = data['Z'] * np.sin(data['Phi'] * np.pi / 180)
    data['R/H'] = data['R'] * 100 / data['身高']
    data['Xc/H'] = data['Xc'] * 100 / data['身高']
    data['Rsp'] = data['R'] * data['BMI']
    data['Xcsp'] = data['Xc'] * data['BMI']
    '''
    r = np.sort(np.array(data['结果']))
    rang = math.ceil(len(r) * drop_range / 2)
    data = data[(data['结果'] > r[rang]) & (data['结果'] < r[-rang])]
    '''
    return data


def pick_data(df):
    R = np.array(df['R/H'])
    X = np.array(df['Xc/H'])
    Rsp = np.array(df['Rsp'])
    Xsp = np.array(df['Xcsp'])
    r = np.array(df['结果'])
    return R, X, Rsp, Xsp, r


from scipy.stats import multivariate_normal


def multivariate_normal_BIVA(R, X):
    return multivariate_normal(np.mean([R, X], axis=1), np.cov(R, X))


# 升序排序并取最小的前percent的数据的序号
def argselect_quartile_min(r, percent, order=None):
    if percent > 1 or percent <= 0:
        raise Exception("percent需满足0<percent<=1")
    return np.argsort(r, order=order)[0:int(len(r) * percent)]


# 选取最大的前percent的数据
def argselect_quartile_max(r, percent, order=None):
    if percent > 1 or percent <= 0:
        raise Exception("percent需满足0<percent<=1")
    if int(len(r) * percent) <= 0:
        return []
    return np.argsort(r, order=order)[-int(len(r) * percent):]


from scipy.stats import stats
from sklearn.linear_model import LinearRegression


def lin_regression(X, y):
    slope, intercept, r_value, p_value, std_err = stats.linregress(X, y)
    model = LinearRegression()
    model.fit(X.reshape(-1, 1), y)
    coef = model.coef_
    inte = model.intercept_
    return slope, intercept, r_value, p_value, std_err


percent = 0.05

translations = {
    '尿素': 'BUN',
    '钙': 'Ca',
    '肌酐': 'Creatinine',
    '白蛋白': 'Albumin',
    '总胆固醇': 'CHOL',
    '低密度脂蛋白胆固醇': 'LDLC',
    '磷': 'Phosphorus',
    '血红蛋白': 'Hb',
    'N端-B型钠尿肽前体': 'NT-proBNP',
    '甲状旁腺素': 'PTH',
    '25-羟维生素D': '25-OH-D3',
    'BMI': 'BMI'
}

translations_file = {
    '尿素': 'BUN',
    '钙': 'Ca',
    '肌酐': 'Cr',
    '白蛋白': 'Alb',
    '总胆固醇': 'CHOL',
    '低密度脂蛋白胆固醇': 'LDLC',
    '磷': 'P',
    '血红蛋白': 'Hb',
    'N端-B型钠尿肽前体': 'NT-proBNP',
    '甲状旁腺素': 'PTH',
    '25-羟维生素D': '25-OH-D3',
    'BMI': 'BMI'
}

translations_total = {
    '尿素': 'Urea',
    '钙': 'Calcium',
    '肌酐': 'Creatinine',
    '白蛋白': 'Albumin',
    '总胆固醇': 'Total Cholesterol',
    '低密度脂蛋白胆固醇': 'Low Density Lipoprotein Cholesterol',
    '磷': 'Phosphorus',
    '血红蛋白': 'Hemoglobin',
    'N端-B型钠尿肽前体': 'N-terminal-B Natriuretic Peptide Precursor',
    '甲状旁腺素': 'Parathyroid Hormone',
    '25-羟维生素D': '25-Hydroxyvitamin D',
    'BMI': 'BMI'
}

units = {
    '尿素': 'mmol/L',
    '钙': 'mmol/L',
    '肌酐': 'umol/L',
    '白蛋白': 'g/L',
    '总胆固醇': 'mmol/L',
    '低密度脂蛋白胆固醇': 'mmol/L',
    '磷': 'mmol/L',
    '血红蛋白': 'g/L',
    'N端-B型钠尿肽前体': 'pg/ml',
    '甲状旁腺素': 'Pg/ml',
    '25-羟维生素D': 'ng/mL',
    'BMI': 'kg/m$^2$'
}

COMPs = ['尿素', '钙', '肌酐', '白蛋白', '总胆固醇', '低密度脂蛋白胆固醇', '磷', '血红蛋白', 'N端-B型钠尿肽前体', '甲状旁腺素', '25-羟维生素D']

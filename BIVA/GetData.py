import pandas as pd
import numpy as np

from 数据连接 import data_dir, SQLf, SQL_to_pandas


def get_data(COMP, SEX):
    """获取数据"""
    data = get_data_from_csv(COMP, SEX)
    data = calculate_data(data)
    data = pick_data(data)
    return data


def get_data_from_database(connection, COMP, SEX):
    """从数据库中获取数据"""
    cursor = connection.cursor()
    cursor.execute(SQLf % (COMP, SEX))
    data = SQL_to_pandas(cursor)
    cursor.close()
    return calculate_data(data)


def get_data_from_csv(COMP, SEX):
    """从csv文件中获取数据"""
    data = pd.read_csv(data_dir + COMP + '-' + SEX + '.csv', encoding='utf8', engine='python')
    return calculate_data(data)


def calculate_data(data):
    """从原始数据计算所需的数据"""
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
    """数据筛选"""
    R = np.array(df['R/H'])
    X = np.array(df['Xc/H'])
    Rsp = np.array(df['Rsp'])
    Xsp = np.array(df['Xcsp'])
    r = np.array(df['结果'])
    return R, X, Rsp, Xsp, r


from NameConf import names, sexes

data = {}

for name in names:
    d = {}
    for sex in sexes:
        d[sex] = get_data(name, sex)
    data[name] = d

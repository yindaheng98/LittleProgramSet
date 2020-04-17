# 化验结果原始数据
file_path = 'G/检验结果.xlsx'  # 原始数据文件
file_encoding = 'UTF8'  # 数据文件编码格式
table_name = '血液成分原始数据'  # 数据库表名
table = {  # 数据库表定义
    '姓名': 'varchar(255) not null',
    '项目': 'varchar(255) not null',
    '成分': 'varchar(255) not null',
    '结果': 'float not null',
    '单位': 'varchar(255) not null',
    '时间': 'datetime not null',
    '情况': 'enum("过量","不足","正常") not null'
}


def convert(row):  # 转换函数把行转化成像上面那个table的格式
    table['姓名'] = row['姓名']
    table['项目'] = row['项目']
    table['成分'] = row['REPORT_ITEM_NAME']
    table['结果'] = float(row['RESULT'])
    table['单位'] = row['UNITS']
    table['时间'] = str(row['RESULT_DATE_TIME'])
    table['情况'] = str(row['REF_LMT'])
    if table['情况'].find('↑') != -1:
        table['情况'] = '过量'
    elif table['情况'].find('↓') != -1:
        table['情况'] = '不足'
    else:
        table['情况'] = '正常'
    return table


def post_process(connection):
    cursor = connection.cursor()
    cursor.execute('SET SQL_SAFE_UPDATES=0')
    connection.commit()
    cursor.execute('UPDATE 血液成分原始数据 SET 单位=RTRIM(LTRIM(单位))')
    cursor.execute('DELETE FROM bcm原始数据 WHERE Phi<0')
    cursor.execute("DELETE FROM 血液成分原始数据 WHERE 成分='白蛋白' AND 单位!='g/L'")
    cursor.execute("DELETE FROM 血液成分原始数据 WHERE 成分='25-羟维生素D' AND 单位!='ng/mL'")
    cursor.execute("UPDATE 血液成分原始数据 SET 单位=substring(单位,2,length(单位)-1) WHERE 单位 LIKE '#%'")
    connection.commit()
    cursor.execute('SET SQL_SAFE_UPDATES=1')
    connection.commit()
    cursor.close()

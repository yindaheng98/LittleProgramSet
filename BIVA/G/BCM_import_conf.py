# BCM原始数据
file_path = 'G/BCMExport.csv'  # 原始数据文件
file_encoding = 'utf-8'  # 数据文件编码格式
table_name = 'BCM原始数据'  # 数据库表名
table = {  # 数据库表定义
    '姓名': 'varchar(255) not null',
    '出生日期': 'date not null',
    '检测日期': 'date not null',
    '性别': 'enum("男","女") not null',
    '体重': 'float not null',
    '身高': 'float not null',
    'Z': 'float not null',
    'Phi': 'float not null'
}


def convert(row):  # 转换函数把行转化成像上面那个table的格式
    table['姓名'] = str(row['Surname'] + row['Name'])
    table['出生日期'] = row['Date of birth']
    table['检测日期'] = row['Date']
    if row['Sex'].find('m') != -1:
        table['性别'] = '男'
    elif row['Sex'].find('f') != -1:
        table['性别'] = '女'
    else:
        print('没有性别数据')
        return None
    table['体重'] = float(row['Weight [kg]'])
    table['身高'] = float(row['Height [cm]'])
    table['Z'] = float(row['Z 50 kHz [Ohm]'])
    table['Phi'] = float(row['Phi 50 kHz [°]'])
    return table


def post_process(connection):
    cursor = connection.cursor()
    cursor.execute('SET SQL_SAFE_UPDATES=0')
    connection.commit()
    cursor.execute('DELETE FROM hospital.bcm原始数据 WHERE ROUND(abs(TIMESTAMPDIFF(DAY, 出生日期, 检测日期))/365)>75')
    connection.commit()
    cursor.execute('SET SQL_SAFE_UPDATES=1')
    connection.commit()
    cursor.close()

from G.connection import connection
from G.Chem_import_conf import file_path, file_encoding, table_name, table, convert, post_process
import pandas as pd

ftype = file_path.split('.')[-1]
if ftype == 'csv':
    data = pd.read_csv(file_path, encoding=file_encoding)
elif ftype == 'xls' or ftype == 'xlsx':
    data = pd.read_excel(file_path, encoding=file_encoding, sheetname=0)
else:
    raise Exception('不支持的文件格式')

cursor = connection.cursor()
# 删表
SQL = 'DROP TABLE IF EXISTS `%s`' % table_name
print(SQL)
cursor.execute(SQL)

# 建表
SQL_create = 'CREATE TABLE `%s`(%%s)' % table_name
columns = ''
for c in table:
    columns += '`%s` %s' % (c, table[c]) + ','
SQL = SQL_create % (columns[0:-1])
print(SQL)
cursor.execute(SQL)

# 插数据
SQL_insert = 'INSERT INTO %s(%s)VALUES(%s)'
columns = ''
columns_f = ''
for c in table:
    columns += '`%s`,' % c
    columns_f += '%%(%s)s,' % c
SQL_insert = SQL_insert % (table_name, columns[0:-1], columns_f[0:-1])

for index, row in data.iterrows():
    try:
        values = convert(row)
    except Exception as e:
        values = None
        print(e)
    if values is None:
        continue
    print(SQL_insert % values)
    cursor.execute(SQL_insert, values)

connection.commit()

# 后处理
post_process(connection)
cursor.close()
connection.close()

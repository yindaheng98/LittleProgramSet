import xlrd
from datetime import datetime
from recycle.xlxsDatetimeToTuple import xlxsDatetimeToTuple

def xlsxReadData(engine, table_name, path, sheetnum=0):
    # 将path路径的excel表格中的数据读入engine所对应的数据库
    workbook = xlrd.open_workbook(path)
    sheet = workbook.sheet_by_index(sheetnum)
    for i in range(1, sheet.nrows):
        row = sheet.row_values(i)
        y, m, d, h, mn, s = xlxsDatetimeToTuple(row[2])
        data = {}
        data['电梯ID'] = int(row[1])
        data['实时时钟'] = datetime(y, m, d, h, mn, s)
        data['运行速度'] = float(row[3])
        data['电压'] = float(row[4])
        data['电流'] = float(row[5])
        data['频率'] = float(row[6])
        data['当前楼层'] = int(row[7])
        data['系统状态'] = str(row[8])
        data['控制器状态'] = str(row[9])
        data['故障描述'] = str(row[10])
        SQL = 'INSERT INTO ' + table_name + ' ' + \
              '(电梯ID,实时时钟,运行速度,电压,电流,频率,当前楼层,系统状态,控制器状态,故障描述) ' + \
              'VALUES(%(电梯ID)s,\"%(实时时钟)s\",%(运行速度)s,%(电压)s,%(电流)s,%(频率)s,%(当前楼层)s,\"%(系统状态)s\",%(控制器状态)s,%(故障描述)s)'
        SQL = SQL % data
        # print(SQL)
        engine.execute(SQL)


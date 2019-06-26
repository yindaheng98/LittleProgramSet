import mysql.connector
from recycle.xlxsDatetimeToTuple import xlxsDatetimeToTuple
cnx=mysql.connector.connect(user='root',password='YHM19980228yhm',
                            host='127.0.0.1',database='lifterdata')
cursor=cnx.cursor()
add_records='INSERT INTO originalrecord_d11\
            (电梯ID,实时时钟,运行速度,电压,电流,频率,当前楼层,系统状态)\
             VALUES(%(电梯ID)s,%(实时时钟)s,%(运行速度)s,%(电压)s,%(电流)s,%(频率)s,%(当前楼层)s,%(系统状态)s)'


import xlrd
from datetime import datetime
workbook=xlrd.open_workbook(r"D:\D11.xlsx")
sheet=workbook.sheet_by_index(0)
rows=sheet.get_rows()
print(sheet.nrows)
for i in range(1,sheet.nrows):
    row=sheet.row_values(i)
    y,m,d,h,mn,s=xlxsDatetimeToTuple(row[2])
    row_data={}
    row_data['电梯ID']=int(row[1])
    row_data['实时时钟']=datetime(y,m,d,h,mn,s)
    row_data['运行速度']=float(row[3])
    row_data['电压']=float(row[4])
    row_data['电流']=float(row[5])
    row_data['频率']=float(row[6])
    row_data['当前楼层']=int(row[7])
    row_data['系统状态']=str(row[8])
    #print(add_records%row_data)
    cursor.execute(add_records,row_data)
    cnx.commit()


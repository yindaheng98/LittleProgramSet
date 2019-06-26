import xlrd
from recycle.xlxsDatetimeToTuple import xlxsDatetimeToTuple
from datetime import datetime
workbook=xlrd.open_workbook(r"D:\D11.xlsx")
sheet=workbook.sheets()[0]

#rows=sheet.get_rows()
for i in range(1,sheet.ncols):
    row=sheet.row_values(i)
    print(type(row[2]))
    y,m,d,h,mn,s=xlxsDatetimeToTuple(row[2])
    print(datetime(y,m,d,h,mn,s))
    
    '''print(int(row[1].value),\
                  datetime(xlxsDatetimeToTuple(row[2].value)),\
                  float(row[3].value),\
                  float(row[4].value),\
                  float(row[5].value),\
                  float(row[6].value),\
                  int(row[7].value),\
                  str(row[8].value))'''

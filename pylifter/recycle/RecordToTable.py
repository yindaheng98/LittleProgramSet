from datetime import datetime
from datetime import datetime
a = datetime(2017, 1, 14, 21, 57, 18)
t='%s'%(a)
print(t)
def RecordToTable(record):
    table={}
    table['电梯ID']=int(''.join(record[3:7]))
    table['实时时钟']=datetime(2000+int(record[7]), \
                           int(record[8]), \
                           int(record[9]), \
                           int(record[10]), \
                           int(record[11]),
                           int(record[12]))
    table['运行速度']
import matplotlib.pyplot as plt
from encode import encode_sys_states
def xlsxDrawData(engine,table_name):
#将指定数据库指定表格中的数据绘制出来
    SQL = 'SELECT * FROM '+ table_name + ' WHERE 系统状态=\'轿厢开门;自行运行状态\''
    result = engine.execute(SQL)
    x = []
    y = []
    temp = 0
    for r in result:
        if not temp == r[6]:
            y.append(r[6])
            t = (r[1].strftime("%Y %m %d %H %M %S")).split(' ')
            x.append(int(t[3]) * 3600 + int(t[4]) * 60 + int(t[5]))
    plt.scatter(x, y, s=3, alpha=0.3)
    plt.show()
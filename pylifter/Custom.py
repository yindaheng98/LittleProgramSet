from datetime import datetime
import re
def DataLineJudge(l):
    #本函数判断输入的行是否是数据行
    l=l[l.find('[')+1:l.find(']')]
    return l.find('55 55 ')==0 and l.find('AA AA ')==138

def DataLineToDict(l):
    # 本函数将字符型的数据列转化为字典

    # 去头去尾取出数据项
    l = l[l.find('[')+1:l.find(']')].split(' ')
    #生成字典
    return {
        '电梯ID' : int(''.join(l[3:7]),16),
        '实时时钟': datetime.strptime(('20'+l[7]+'-'+l[8]+'-'+l[9]+' '+l[10]+':'+l[11]+':'+l[12]),"%Y-%m-%d %H:%M:%S"),
        '运行速度': float(int(l[13] + l[14], 16) / 1000),
        '母线电压': float(int(l[15] + l[16], 16) / 10),
        '母线电流': float(int(l[17] + l[18], 16) / 1000),
        '频率': float(int(l[19] + l[20], 16) / 10),
        '当前楼层': int(l[21] + l[22], 16),
        '系统状态': int(l[24][0], 16),
        '轿厢状态': int(l[23][1], 16),
        '控制器状态': int(l[25], 16),
        '故障描述': int(l[26] + l[27], 16)
    }

def DataDictToTablename(dict):#本函数从数据字典中判断该行数据应被插入哪个表
    return 'lifter_'+str(dict['电梯ID'])




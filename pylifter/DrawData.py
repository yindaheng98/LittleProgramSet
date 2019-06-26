import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

from encode import encode_car_states

def DrawData_DoorOpen(engine,table_name):
#将指定数据库指定表格中的数据绘制出来
    SQL = 'SELECT * FROM '+ table_name + ' WHERE 轿厢状态='+str(encode_car_states['轿厢开门'])
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


def DrawData_OfflineJudge(engine,table_name,lifterID,maxtime_assume):
    # 计算某台电梯的发信间隔时间分布
    #lifterID为电梯ID，maxtime_assume为假设的间隔时间最大值，scaling为缩放比（柱状图中每个柱子包含多少时间/秒）
    SQL = 'SELECT DISTINCT 实时时钟 FROM ' + table_name + ' WHERE 电梯ID=' + str(lifterID) + ' ORDER BY 实时时钟'
    times = engine.execute(SQL)

    # 计算并存储时间间隔
    ins_times = [0] * int(maxtime_assume+1)
    t_last = 0
    for time in times:
        if t_last == 0:  # t_last为空说明是第一个
            t_last = time[0]  # 赋初值并跳到下一个
            continue
        else:
            # 计算并存储间隔时间
            ins=(time[0] - t_last).seconds
            ins_times[ins if ins<=maxtime_assume else maxtime_assume] += 1
            t_last = time[0]
    return ins_times


def Draw_OfflineJudge(engine,table_name, maxtime_assume):
    #掉线问题相关绘图函数
    #选出所有电梯编号
    SQL='SELECT DISTINCT 电梯ID FROM '+table_name+' ORDER BY 电梯ID'
    lifters=engine.execute(SQL)
    # 算出每个电梯的时间数据
    data=[]
    for lifter in lifters:
        data=DrawData_OfflineJudge(engine, table_name, str(lifter)[1:-2], maxtime_assume)
        # 绘图
        #print(data)
        plt.bar(range(len(data)), data, width=10)
        plt.title('lifter_'+str(lifter)[1:-2])
        plt.show()


def DrawData_OfflineCount(engine,table_name,lifterID,time_range):
    #统计在各层掉线时间超过设定值floor_range的次数
    #floor_range为设定的异常阈
    SQL='SELECT DISTINCT 实时时钟,当前楼层 FROM ' + table_name + ' WHERE 电梯ID=' + str(lifterID) + ' ORDER BY 实时时钟'
    total=engine.execute(SQL)
    last=0#记录上一个楼层-时间组合的值
    count=[0]*10#记录掉线的楼层
    for now in total:#遍历所有数据
        short = now[1] - len(count)
        if short >= 0:  # 如果长度不够就要扩展
            count.extend([0] * (short + 1))
        if last==0:#如果是第一个
            last=now#赋初值
            continue
        else:#否则展开计算
            ins=(now[0]-last[0]).seconds#间隔时间以秒记
            if ins>=time_range and abs(now[1]-last[1])<=1:#若超出正常范围而且电梯是停止的（楼层变化小于2）则记录
                count[now[1]]+=1
            last=now
    print(count)
    return count


def DrawData_OfflineTimeSquare(engine,table_name,lifterID,maxtime_assume):
    #统计在各层各掉线时间(秒)的次数
    #maxtime_assume为假设的间隔时间最大值
    SQL='SELECT DISTINCT 实时时钟,当前楼层 FROM ' + table_name + ' WHERE 电梯ID=' + str(lifterID) + ' ORDER BY 实时时钟'
    total=engine.execute(SQL)
    last=0#记录上一个楼层-时间组合的值
    count=[[0]*maxtime_assume]#count(掉线时间，掉线楼层)
    for now in total:#遍历所有数据,now为（实时时钟，当前楼层）
        short = now[1] - len(count)
        if short >= 0:  # 如果楼层长度不够就要扩展
            for i in range(short+1):
                count.append([0]*maxtime_assume)
        if last==0:#如果是第一个
            pass#赋初值
        else:#否则展开计算
            ins=(now[0]-last[0]).seconds#间隔时间以秒记
            if abs(now[1]-last[1])<=1:#若电梯是停止的（楼层变化小于2）则记录
                count[now[1]][ins if ins<maxtime_assume else maxtime_assume-1]+=1
        last=now
    return count


def DrawData_OfflineTime_DropZero(engine,table_name,lifterID,maxtime_assume):
    #画3d柱状图的数据
    floors=[]
    times=[]
    count=[]
    square=DrawData_OfflineTimeSquare(engine, table_name, lifterID, maxtime_assume)
    for floor in range(0,len(square)):
        for time in range(0,len(square[floor])):
            if square[floor][time]!=0:#统计出不为0的项画3d柱状图
                floors.append(floor)
                times.append(time)
                count.append(square[floor][time])
    return floors,times,count


def Draw_OfflineTime(engine,table_name,lifterID,maxtime_assume,maxcount):
    fig = plt.figure()
    ax = Axes3D(fig)
    #ax.view_init(azim=25)
    data=DrawData_OfflineTimeSquare(engine,table_name,lifterID,maxtime_assume)
    for floor in range(len(data)):
        times = []
        count = []
        for time in range(len(data[floor])):
            if data[floor][time]!=0:
                times.append(time)
                count.append(data[floor][time] if data[floor][time]<=maxcount else maxcount)
        ax.bar(times,count,floor,zdir='y',width=100,alpha=0.5)
    plt.title('lifter_'+str(lifterID))
    ax.set_xlabel(r'掉线时长')
    ax.set_ylabel(r'楼层')
    ax.set_zlabel(r'掉线次数')
    #plt.show()
    plt.savefig('D:/'+'lifter_'+str(lifterID)+'.png', format='png', dpi=300)
    plt.clf()



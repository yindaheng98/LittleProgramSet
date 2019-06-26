import LifterClass
import datetime


init_time = datetime.datetime(2014, 8, 15, 9, 57, 52, 779893)
lf = LifterClass.Lifter_linear_constant_a(3, 2, 3, 15, -3)
lf.setCondition(init_time, 0, 0, 2, '上行')
for i in range(1, 40):
    init_time += datetime.timedelta(0, 0, 500000)
    h, v, a = lf.getCondition(init_time)
    print(h)
lf.giveCommand('下行', init_time)
for i in range(1, 20):
    init_time += datetime.timedelta(0, 0, 500000)
    h, v, a = lf.getCondition(init_time)
    print(h)
lf.giveCommand('上行', init_time)
for i in range(1, 40):
    init_time += datetime.timedelta(0, 0, 500000)
    h, v, a = lf.getCondition(init_time)
    print(h)



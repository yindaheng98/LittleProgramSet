from EventLoop import EventLoop
from Q import Q
import random
from theory import MMn
import matplotlib.pyplot as plt
import numpy as np

'''初始化配置'''
N = 30000
_lambda = 3.
_miu = 5.
n = 3

'''运行时配置'''
event_loop = EventLoop()
q = Q(event_loop, _miu, n)


def ArriveCallback(_lambda):
    global N
    N -= 1
    arrive_interval = random.expovariate(_lambda)  # 随机生成到达时间间隔
    event_loop.setTimeout(arrive_interval, lambda: ArriveCallback(_lambda))  # 一定时间后再次到达
    q.arrive()


event_loop.setTimeout(0, lambda: ArriveCallback(_lambda))
event_loop.loopUntil(lambda: N <= 0)
print("Elq=%f" % q.Elq())
print("Elq=%f" % MMn(n, _lambda, _miu))

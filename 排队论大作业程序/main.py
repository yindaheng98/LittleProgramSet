from EventLoop import EventLoop
from Queue import Queue
import random

'''初始化配置'''
N = 1000
_lambda = 1.
_miu = 1.
n = 3

'''运行时配置'''
event_loop = EventLoop()
q = Queue(event_loop, _miu, n)


def ArriveCallback(_lambda):
    global N
    N -= 1
    arrive_interval = random.expovariate(_lambda)  # 随机生成到达时间间隔
    event_loop.setTimeout(arrive_interval, lambda: ArriveCallback(_lambda))  # 一定时间后再次到达
    q.arrive()


event_loop.setTimeout(0, lambda: ArriveCallback(_lambda))
event_loop.loopUntil(lambda: N <= 0)

import random

from EventLoop import EventLoop
from Q import Q


class MMnSimulator:
    def __init__(self, _lambda, _miu, n):
        self._lambda = _lambda
        self._miu = _miu
        self.n = n
        self.event_loop = None
        self.q = None
        self.N = 0

    def start(self, N):
        self.event_loop = EventLoop()
        self.q = Q(self.event_loop, self._miu, self.n)
        self.N = N
        self.event_loop.setTimeout(0, lambda: self.__arrive_callback())
        self.event_loop.loopUntil(lambda: self.N <= 0)

    def __arrive_callback(self):
        self.N -= 1
        arrive_interval = random.expovariate(self._lambda)  # 随机生成到达时间间隔
        self.event_loop.setTimeout(arrive_interval, lambda: self.__arrive_callback())  # 一定时间后再次到达
        self.q.arrive()


MMn = MMnSimulator(_lambda, _miu, n)
MMn.start(30000)
print("Elq=%f" % MMn.q.Elq())

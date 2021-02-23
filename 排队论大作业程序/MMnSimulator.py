import math
import random

from EventLoop import EventLoop
from Q import Q


class MMnSimulator:
    def __init__(self, _lambda, _miu, n):
        self._lambda = float(_lambda)
        self._miu = float(_miu)
        self.n = int(n)
        self.event_loop = None
        self.q = None
        self.N = 0

    def run(self, N):
        self.event_loop = EventLoop()
        self.q = Q(self.event_loop, self._miu, self.n)
        self.N = N
        self.event_loop.setTimeout(0, lambda: self.__arrive_callback())
        self.event_loop.loopUntil(lambda: self.N <= 0)
        return self.q.Elq()

    def __arrive_callback(self):
        self.N -= 1
        arrive_interval = random.expovariate(self._lambda)  # 随机生成到达时间间隔
        self.event_loop.setTimeout(arrive_interval, lambda: self.__arrive_callback())  # 一定时间后再次到达
        self.q.arrive()

    def theory(self):
        _lambda, _miu, n = self._lambda, self._miu, self.n
        rho = _lambda / _miu
        P0 = 1 / (
                sum([rho ** i / math.factorial(i) for i in range(0, n + 1)]) +
                rho ** (n + 1) / (math.factorial(n) * (n - rho))
        )
        Elq = (rho ** (n + 1) * P0) / (n * math.factorial(n) * (1 - rho / n) ** 2)
        return Elq

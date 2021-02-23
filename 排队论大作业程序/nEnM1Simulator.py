import random

from EventLoop import EventLoop
from Q import Q
import numpy as np


class nEnM1Simulator:
    def __init__(self, _lambda, _miu, n):
        self._lambda = float(_lambda)
        self._miu = float(_miu)
        self.n = int(n)
        self.k = int(n)
        self.Elq_theory = self.__Elq_theory()

        self.event_loop = None
        self.q = []
        self.N = 0

    def run(self, N):
        self.event_loop = EventLoop()
        self.q = []
        for i in range(0, self.n):
            self.q.append(Q(self.event_loop, self._miu, 1))
        self.N = N
        for i in range(0, self.n):
            l = lambda j: lambda: self.__arrive_callback(j)
            self.event_loop.setTimeout(0, l(i))
        self.event_loop.loopUntil(lambda: self.N <= 0)
        return sum([q.Elq() for q in self.q])

    def __arrive_callback(self, i):
        self.N -= 1
        arrive_interval = 0
        for _ in range(0, self.k):
            arrive_interval += random.expovariate(self.k * self._lambda)  # 随机生成到达时间间隔
        self.event_loop.setTimeout(arrive_interval, lambda: self.__arrive_callback(i))  # 一定时间后再次到达
        self.q[i].arrive()

    def __Elq_theory(self):
        _lambda, _miu, n, k = self._lambda, self._miu, self.n, self.k
        rho = _lambda / _miu
        params = [1.] * self.k
        params.append(-self.k * rho)
        rs = np.roots(params)
        rs = np.real(rs[~np.iscomplex(rs)])
        r = np.min(rs[rs >= 0.])
        Elq = (rho * r ** k / (1 - r ** k)) * n
        return Elq

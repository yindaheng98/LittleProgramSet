import random

from EventLoop import EventLoop
from Q import Q


class nMM1Simulator:
    def __init__(self, _lambda, _miu, n):
        self._lambda = float(_lambda)
        self._miu = float(_miu)
        self.n = int(n)
        self.Elq_theory = self.__Elq_theory()

        self.event_loop = None
        self.q = []
        self.N = 0

    def run(self, N):
        self.event_loop = EventLoop()
        self.q = []
        for _ in range(0, self.n):
            self.q.append(Q(self.event_loop, self._miu, 1))
        self.N = N
        self.event_loop.setTimeout(0, lambda: self.__arrive_callback())
        self.event_loop.loopUntil(lambda: self.N <= 0)
        return sum([q.Elq() for q in self.q])

    def __arrive_callback(self):
        self.N -= 1
        arrive_interval = random.expovariate(self._lambda)  # 随机生成到达时间间隔
        self.event_loop.setTimeout(arrive_interval, lambda: self.__arrive_callback())  # 一定时间后再次到达
        self.q[random.randint(0, self.n - 1)].arrive()

    def __Elq_theory(self):
        _lambda, _miu, n = self._lambda, self._miu, self.n
        Elq = (_lambda / n) ** 2 / (_miu * (_miu - _lambda / n))
        return Elq * n

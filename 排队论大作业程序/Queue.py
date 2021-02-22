from EventLoop import EventLoop
import random


class Queue:
    def __init__(self, event_loop: EventLoop, _miu: float, n: int = 1):
        self.event_loop = event_loop
        self.n = n  # 闲置服务员数量
        self.queue_length = 0  # 当前队列长度
        self._miu = _miu  # 服务过程为泊松过程，其μ值

    def arrive(self):
        print("tick:%f, 队列长度=%d, 服务员闲置数=%d, 顾客到达" % (self.event_loop.tick, self.queue_length, self.n))
        self.queue_length += 1  # 进队列
        if self.n > 0:  # 如果有服务员闲
            self.__serve_begin()  # 开始服务

    def __serve_begin(self):
        print("tick:%f, 队列长度=%d, 服务员闲置数=%d, 开始服务" % (self.event_loop.tick, self.queue_length, self.n))
        self.n -= 1  # 闲置服务员-1
        self.queue_length -= 1  # 队列长度-1
        serve_interval = random.expovariate(self._miu)  # 随机生成服务时间
        self.event_loop.setTimeout(serve_interval, lambda: self.__serve_end())  # 一定时间后结束服务

    def __serve_end(self):
        print("tick:%f, 队列长度=%d, 服务员闲置数=%d, 结束服务" % (self.event_loop.tick, self.queue_length, self.n))
        self.n += 1  # 闲置服务员+1
        if self.queue_length > 0:  # 如果队列中还有顾客
            self.__serve_begin()  # 开始服务

from EventLoop import EventLoop
import random


def log(tick, queue_length, n, info):
    print("(队列长度,服务员闲置数)tick:%f:(%d, %d)--%s-->(%d, %d), " %
          (tick, queue_length[0], n[0], info, queue_length[1], n[1]))


class Queue:
    def __init__(self, event_loop: EventLoop, _miu: float, n: int = 1):
        self.event_loop = event_loop
        self.n = n  # 闲置服务员数量
        self.queue_length = 0  # 当前队列长度
        self._miu = _miu  # 服务过程为泊松过程，其μ值
        self.result = []

    def __record(self):
        self.result.append([self.event_loop.tick, self.queue_length])  # 记录当前队列长度

    def Elq(self):
        lq = 0
        queue_length_last = self.result[0]
        for queue_length in self.result[1:]:
            lq += queue_length_last[1] * (queue_length[0] - queue_length_last[0])
            queue_length_last = queue_length
        return lq / (self.result[-1][0] - self.result[0][0])

    def arrive(self):
        self.__record()
        log(self.event_loop.tick, (self.queue_length, self.queue_length + 1), (self.n, self.n), "顾客到达")
        self.queue_length += 1  # 进队列
        if self.n > 0:  # 如果有服务员闲置
            self.__serve_begin()  # 开始服务
        self.__record()

    def __serve_begin(self):
        self.__record()
        log(self.event_loop.tick, (self.queue_length, self.queue_length - 1), (self.n, self.n - 1), "开始服务")
        self.n -= 1  # 闲置服务员-1
        self.queue_length -= 1  # 队列长度-1
        serve_interval = random.expovariate(self._miu)  # 随机生成服务时间
        self.event_loop.setTimeout(serve_interval, lambda: self.__serve_end())  # 一定时间后结束服务
        self.__record()

    def __serve_end(self):
        log(self.event_loop.tick, (self.queue_length, self.queue_length), (self.n, self.n + 1), "完成服务")
        self.n += 1  # 闲置服务员+1
        if self.queue_length > 0:  # 如果队列中还有顾客
            self.__serve_begin()  # 开始服务

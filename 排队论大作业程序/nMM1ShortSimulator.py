from nMM1Simulator import nMM1Simulator
import random


def find_min(qs):
    l = [q.queue_length for q in qs]
    m = min(l)
    idx = [i for i, x in enumerate(l) if x == m]
    return random.choice(idx)  # 如果最小值有多个就随机选一个


class nMM1ShortSimulator(nMM1Simulator):
    def __init__(self, _lambda, _miu, n):
        super().__init__(_lambda, _miu, n, selector=find_min)

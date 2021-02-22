class EventLoop:
    def __init__(self):
        self.tick = 0
        self.eventList = {}

    def setTimeout(self, timeout, callback):
        if timeout not in self.eventList:  # 如果还没有这个interval的事件列表
            self.eventList[timeout] = []  # 就创建
        self.eventList[timeout].append(callback)  # 添加事件

    def loop(self):
        interval = sorted(self.eventList)[0]  # 获取最近的事件发生的时间
        self.tick += interval  # 直接跳转到这个时间
        oldEventList = self.eventList  # 保存旧的事件列表
        self.eventList = {}
        for callback in oldEventList[interval]:  # 最近的事件
            callback()  # 保存旧的事件列表就是因为这个callback里面可能产生新的事件
        del oldEventList[interval]  # 删除已运行的事件列表
        for old_interval in oldEventList:  # 将剩下的事件列表加到新的事件列表里面
            new_interval = old_interval - interval  # 更新时间
            if new_interval in self.eventList:  # 如果已经有这个interval的事件列表
                self.eventList[new_interval].extend(oldEventList[old_interval])  # 就扩展
            else:
                self.eventList[new_interval] = oldEventList[old_interval]  # 否则新建

    def loopUntil(self, stop):
        while not stop():
            self.loop()

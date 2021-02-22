class EventLoop:
    def __init__(self):
        self.tick = 0
        self.eventList = {}

    def setTimeout(self, timeout, callback):
        if timeout not in self.eventList:
            self.eventList[timeout] = []
        self.eventList[timeout].append(callback)

    def loop(self):
        interval = sorted(self.eventList)[0]
        self.tick += interval
        for cb in self.eventList[interval]:
            cb()
        del self.eventList[interval]
        eventList_next = {}
        for t in self.eventList:
            eventList_next[t - interval] = self.eventList[t]
        self.eventList = eventList_next

    def loopUntil(self, stop):
        while not stop():
            self.loop()

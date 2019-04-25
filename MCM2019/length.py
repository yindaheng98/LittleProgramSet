import math
import matplotlib.pyplot as plt

class Point:
    def __init__(self,lat,lon):
        self.lat=lat*math.pi/180
        self.lon=lon*math.pi/180
    
    def __str__(self):
        return '经度'+str(self.lat/math.pi*180)+'纬度'+str(self.lon/math.pi*180)
    
    def copy(self):
        return Point(self.lat/math.pi*180,self.lon/math.pi*180)

class Network:
    def __init__(self,sources=[],destinations=[]):
        for p in sources:
            if not isinstance(p,Point):
                raise BaseException('点必须是Point类型！')
        for p in destinations:
            if not isinstance(p,Point):
                raise BaseException('点必须是Point类型！')
        self.sources=sources
        self.destinations=destinations
    
    def add_source(self,p):
        if not isinstance(p,Point):
            raise BaseException('点必须是Point类型！')
        self.sources.append(p.copy())
        
    def add_destination(self,p):
        if not isinstance(p,Point):
            raise BaseException('点必须是Point类型！')
        self.destinations.append(p.copy())
        
    @staticmethod
    def length(p1,p2):
        R=6371004#地球半径
        C = math.sin(p1.lat)*math.sin(p2.lat)*math.cos(p1.lon-p2.lon) + math.cos(p1.lat)*math.cos(p2.lat)
        return R*math.acos(C)
    
    @staticmethod
    def cal_minlength_single(p0,ps):#计算某个点到其他一些点的距离的最小值
        lmin=float('inf')
        pmin=None
        for p in ps:
            l=Network.length(p0,p)
            if l<lmin:
                lmin=l
                pmin=p.copy()
        return lmin,pmin#返回(距离最小值,最小值的那个点)
    
    def minlength(self):
        #一个destination对一个source，一个source对多个destination
        #使找出到destination的距离最短的source
        self.lmin=0
        self.pmins=[]
        for destination in self.destinations:
            lmin,pmin=Network.cal_minlength_single(destination,self.sources)
            self.lmin+=lmin
            self.pmins.append(pmin.copy())
        return self.lmin,self.pmins
    
#测试
nw=Network()
nw.add_destination(Point(18.33,-65.65))
nw.add_destination(Point(18.22,-66.03))
nw.add_destination(Point(18.44,-66.07))
nw.add_destination(Point(18.40,-66.16))
nw.add_destination(Point(18.47,-66.73))
nw.add_source(Point(18.22,-66.03))
nw.add_source(Point(18.44,-66.07))
nw.add_source(Point(18.40,-66.16))
for p in nw.destinations:
    print(p)
lmin,pmins=nw.minlength()
print(lmin)
for p in pmins:
    print(p)

cur=0.1
search_points=[]
for lat in range(math.floor(18.22/cur),math.ceil(18.47/cur)+1):
    for lon in range(math.floor(-66.73/cur),math.ceil(-65.65/cur)+1):
        search_points.append(Point(lat*cur,lon*cur))
len(search_points)
for search_point in search_points:
    print(search_point)

hospitals=[Point(18.33,-65.65),Point(18.22,-66.03),Point(18.44,-66.07),Point(18.40,-66.16),Point(18.47,-66.73)]
lmin3=float('inf')
pmins3=[]
for p1 in search_points:
    for p2 in search_points:
        for p3 in search_points:
            containers=[p1,p2,p3]
            nw=Network(sources=containers,destinations=hospitals)
            lmin,pmins=nw.minlength()
            if lmin<lmin3:
                lmin3=lmin
                pmins3=pmins

print(lmin3)
for pmin in pmins3:
    print(pmin)

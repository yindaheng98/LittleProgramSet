import math

"""定义盒子"""
class Box:
    def __init__(self,size):
        for s in size:
            if s<=0:
                raise BaseException('box边长不能为0')
        self.x,self.y,self.z=tuple(size)
    
    """输入True改变装载方向(一种转法，不能倒放)
    返回改了装载方向的盒子"""
    def turn(self):
        return Box([self.y,self.x,self.z])
    
    def transpose(self,trans_type):
        size=[self.x,self.y,self.z]
        #x和x或y或z互换(x和size[trans_type%3]互换)
        x=size[0]
        size[0]=size[trans_type%3]
        size[trans_type%3]=x
        #yz互换(trans_type%2==1则换)
        if trans_type%2==1:
            y=size[1]
            size[1]=size[2]
            size[2]=y
        return Box(size)
    
    def reverse_transpose(self,trans_type):#恢复旋转
        size=[self.x,self.y,self.z]
        return Box(self.tuple_reverse_transpose(size,trans_type))
    
    @staticmethod
    def tuple_reverse_transpose(size,trans_type):#恢复旋转
        size=list(size)
        #yz互换(trans_type%2==1则换)
        if trans_type%2==1:
            y=size[1]
            size[1]=size[2]
            size[2]=y
        #x和x或y或z互换(x和size[trans_type%3]互换)
        x=size[0]
        size[0]=size[trans_type%3]
        size[trans_type%3]=x
        return tuple(size)
    
    def size(self):
        return (self.x,self.y,self.z)
    
    """这个box减去一个box的结果
    返回组成剩余空间的四个box，
    z方向上不分层"""
    def __sub__(self,box):
        xr=self.x-box.x
        yr=self.y-box.y
        zr=self.z-box.z
        if xr<0 or yr<0 or zr<0:
            raise BaseException("装不下")
        boxrs=[]
        if zr!=0:
            boxrs.append(Box([self.x,self.y,zr]))
        if yr!=0:
            boxrs.append(Box([box.x,yr,box.z]))
        if xr!=0:
            boxrs.append(Box([xr,box.y,box.z]))
        if xr!=0 and yr!=0:
            boxrs.append(Box([xr,yr,box.z]))
        return boxrs
        
    """这个box加上一个box的结果"""
    def __add__(self,box):
        return 0
        
    """print尺寸"""
    def __str__(self):
        return ('长'+str(self.x)+',宽'+str(self.y)+',高'+str(self.z))

#测试
bx=Box([1,2,3])
print(bx.turn())
print(bx)
print(bx.size())
subx=bx-Box([0.4,1.2,2])
print(subx[3])

bx=Box([1,2,3]).transpose(2)
print(bx)
print(bx.reverse_transpose(2))

"""定义货物"""
class Cargo(Box):
    def __init__(self,size,n,m=0):
        super(Cargo,self).__init__(size)
        self.n=n
        self.m=m
    
    """输入0/1/2改变装载方向
    返回改了装载方向的货物"""
    def turn(self):
        cargo=super(Cargo,self).turn()
        return Cargo(cargo.size(),self.n)
    
    def transpose(self,trans_type):
        if not (trans_type in [0,2,3]):
            raise BaseException('药品不能倒放')
        cargo=super(Cargo,self).transpose(trans_type)
        return Cargo(cargo.size(),self.n)
    
    def reverse_transpose(self,trans_type):#恢复旋转
        cargo=super(Cargo,self).reverse_transpose(trans_type)
        return Cargo(cargo.size(),self.n)
        
    def __str__(self):
        return '货物-'+super(Cargo,self).__str__()+',数量'+str(self.n)+',质量'+str(self.m)
    
#测试
print('测试')
cg=Cargo([1,2,3],5)
print(cg.turn())
print(cg)
print(cg.size())

"""box-一个集装箱，cargo-一种货物，
装箱维度不变，xy方向填满，z方向变化，
输出装载方案[各方向并排货物数(nx,ny,nz),剩余空间Box([x,y,z])]
使装入的每种货物数量仅仅大于要求数量"""
def load_meds(box,cargo):
    if(not isinstance(box,Box) or not isinstance(cargo,Cargo)):
        raise BaseException("类型不对")
    nx_max=math.floor(box.x/cargo.x)
    ny_max=math.floor(box.y/cargo.y)
    nz_max=math.floor(box.z/cargo.z)
    n_max=nx_max*ny_max*nz_max#计算各维度的最多箱子数量，以及总的最多箱子数量
    nz=nz_max if n_max<=cargo.n else math.ceil(cargo.n/(nx_max*ny_max))
    if n_max>0:
        return (nx_max,ny_max,nz),box-Box([nx_max*cargo.x,ny_max*cargo.y,nz*cargo.z])
    else:
        return (nx_max,ny_max,nz),[Box([box.x,box.y,box.z])]

#测试
cs,boxrs=load_meds(Box([231,92,94]),Cargo([12,7,4],60))
print(cs)
for boxr in boxrs:
    print(boxr)

def load_meds_trans(box,cargo,trans_type):
    n_size,boxrs=load_meds(box.transpose(trans_type),cargo.transpose(trans_type))
    n_size=Box.tuple_reverse_transpose(n_size,trans_type)
    boxrs=[b.reverse_transpose(trans_type) for b in boxrs]
    return n_size,boxrs

#测试
cs,boxrs=load_meds_trans(Box([231,92,94]),Cargo([12,7,4],60),2)
print(cs)
for boxr in boxrs:
    print(boxr)

def best_boxload(box,cargos):
    if cargos==[]:
        return [box],[]
    n_min=float('inf')
    n_size_min=''
    r_box_min=''
    turn=0
    for trans_type in [0,2,3]:
        for i in range(2):
            n_size,r_box=load_meds_trans(box,cargos[0].turn() if i==1 else cargos[0],trans_type)
            n=n_size[0]*n_size[1]*n_size[2]
            if n<n_min:
                n_min=n
                n_size_min=n_size
                r_box_min=r_box
                turn=i==1
    
    #装载计划：[剩余空间box序列],[(旋转方向,(三个维度的数量)),]
    r_box,r_load_plan=best_boxload(r_box_min[0],cargos[1:])
    return r_box_min[1:]+r_box,[(turn,n_size_min)]+r_load_plan

#测试
box=Box([231,92,94])
meds=[]
meds.append(Cargo([14,7,5],60))
meds.append(Cargo([5,8,5],30))
meds.append(Cargo([12,7,4],60))
r_box,load_plan=best_boxload(box,meds)
print(r_box[-1])
print(load_plan)

def max_loads(box,cargos,max_m):
    load_lists=[[0]*len(cargos)]
    for t in range(len(cargos)):
        load_lists_t=load_lists
        load_lists=[]
        for load_list in list(load_lists_t):
            for n in range(cargos[t].n+1):
                load_list=list(load_list)
                load_list[t]=n
                load_lists.append(load_list)
    load_plans=[]
    for load_list in load_lists:#计算每种装载方案
        m=0
        for t in range(len(cargos)):#计算总重
            m+=cargos[t].m*load_list[t]
        if m<=max_m:#不超重才继续算
            #到这里，我们有了一个货物列表和一个不超重的load_list
            #以下计算装载方案
            cargos_t={}
            for t in range(len(cargos)):
                if load_list[t]>0:#构造一个临时的货物列表，其中放着load_list中不为0的货物
                    cargos_t[t]=Cargo(cargos[t].size(),load_list[t])
            if sum(load_list)>0:
                r_box,load_plan=best_boxload(box,list(cargos_t.values()))
                load_plan_t={}
                for v in zip(list(cargos_t.keys()),load_plan):
                    load_plan_t[v[0]]=v[1]
                load_plans.append(load_plan_t)
    return load_plans
#测试
box=Box([8,10,14])
#box=Box([24,20,20])
meds=[]
meds.append(Cargo([14,7,5],n=100,m=2))
meds.append(Cargo([5,8,5],n=100,m=2))
meds.append(Cargo([12,7,4],n=100,m=3))
max_loads(box,meds,22)

"""定义无人机"""
class Drone(Box):
    def __init__(self,size,max_load,speed,flight_time,video,load_lists=[]):
        super(Drone,self).__init__(size)
        self.max_load=max_load
        self.speed=speed
        self.flight_time=flight_time
        self.video=video
        self.get_load_lists(load_lists)
    
    """输入0/1/2改变装载方向
    返回改了装载方向的货物"""
    def turn(self):
        drone=super(Drone,self).turn()
        return Drone(drone.size(),self.max_load,self.speed,self.flight_time,self.video)
    
    def transpose(self,trans_type):
        drone=super(Drone,self).transpose(trans_type)
        return Drone(drone.size(),self.max_load,self.speed,self.flight_time,self.video)
    
    def reverse_transpose(self,trans_type):#恢复旋转
        drone=super(Drone,self).reverse_transpose(trans_type)
        return Drone(drone.size(),self.max_load,self.speed,self.flight_time,self.video)
    
    def get_load_lists(self,load_lists):
        self.load_lists=[]
        for ls in load_lists:
            lst={}
            for c in ls.keys():
                lst[c]=ls[c]
            self.load_lists.append(lst)
    
    def __str__(self):
        s='无人机-'+super(Drone,self).__str__()
        s+=',最大载重'+str(self.max_load)
        s+=',速度'+str(self.speed)
        s+=',飞行时间'+str(self.flight_time)
        s+=',带摄像机'+str(self.video)
        s+=',候选装载列表'+str(self.load_lists)
        return s
    
    
#测试
print('测试')
cg=Drone([1,2,3],5,3,4,True)
print(cg.turn())
print(cg)
print(cg.size())
print(cg.transpose(2))

drones=[]
load_list=[{1:2}]
drones.append(Drone([30,30,22],8,79,40,True,load_list))
load_list=[{0:7},{1:7},{2:4}]
drones.append(Drone([60,50,30],14,64,35,True,load_list))
load_list=[{1:2}]
drones.append(Drone([25,20,25],11,60,18,True,load_list))
load_list=[{0:7},{1:7},{2:5}]
drones.append(Drone([25,20,27],15,60,15,True,load_list))
load_list=[{0:8},{1:11},{2:7}]
drones.append(Drone([40,40,25],22,79,24,False,load_list))
load_list=[{0:8},{1:10},{2:6}]
drones.append(Drone([32,32,17],20,64,16,True,load_list))
for drone in drones:
    print(drone)

class Deliver:
    def __init__(self,box,cargos,drones):
        self.cargos_dict,self.r_box=Deliver.get_cargos_load_plan(box,cargos)
        self.drones_dict=modify_drones(self.r_box,self.cargos_dict,drones)
       
    @staticmethod
    def get_cargos_load_plan(box,cargos):
        r_box,load_plan=best_boxload(box,cargos)
        r_box=r_box[-1]
        cargos_dict={}
        for i in range(len(cargos)):#求load_list
            ni=load_plan[i][1][0]*load_plan[i][1][1]*load_plan[i][1][2]
            if ni>0:
                cargos_dict[i]=Cargo(cargos[i].size(),cargos[i].n,cargos[i].m)
        return cargos_dict,r_box
    
    @staticmethod
    def modify_drones(box,cargos_dict,drones_dict):#返回[(无人机类型,无人机数量)]
        cargos_num={}
        for i,cargo in cargos_dict:
            cargos_num[i]=cargo.n
        
        return 0
        
    
#测试
box=Box([231,92,94])

meds=[]
meds.append(Cargo([14,7,5],60,2))
meds.append(Cargo([5,8,5],30,2))
meds.append(Cargo([12,7,4],60,3))

drones=[]
load_list=[{1:2}]
drones.append(Drone([30,30,22],8,79,40,True,load_list))
load_list=[{0:7},{1:7},{2:4}]
drones.append(Drone([60,50,30],14,64,35,True,load_list))
load_list=[{1:2}]
drones.append(Drone([25,20,25],11,60,18,True,load_list))
load_list=[{0:7},{1:7},{2:5}]
drones.append(Drone([25,20,27],15,60,15,True,load_list))
load_list=[{0:8},{1:11},{2:7}]
drones.append(Drone([40,40,25],22,79,24,False,load_list))
load_list=[{0:8},{1:10},{2:6}]
drones.append(Drone([32,32,17],20,64,16,True,load_list))
dl=Deliver(box,meds,drones)

print(dl.r_box)
for cargo in dl.cargos_dict.values():
    print(cargo)
for drone in dl.drones:
    print(drone)

r_box=Box([212,92,94])

#r_drones=[Cargo([30,30,22],100)]

r_drones=[Cargo([60,50,30],100)]
rr_box,load_plan=best_boxload(r_box,r_drones)
print(rr_box[-1])
print(load_plan)

#r_drones=[Cargo([25,20,25],100)]

r_drones=[Cargo([25,20,27],100)]
rr_box,load_plan=best_boxload(r_box,r_drones)
print(rr_box[-1])
print(load_plan)

r_drones=[Cargo([40,40,25],100)]
rr_box,load_plan=best_boxload(r_box,r_drones)
print(rr_box[-1])
print(load_plan)

r_drones=[Cargo([32,32,17],100)]
rr_box,load_plan=best_boxload(r_box,r_drones)
print(rr_box[-1])
print(load_plan)

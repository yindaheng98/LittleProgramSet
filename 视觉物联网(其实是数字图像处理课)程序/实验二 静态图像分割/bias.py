import numpy as np
import cv2
import math

img = cv2.imread('drop_center/img5.jpg',cv2.IMREAD_GRAYSCALE)
img=(img>128).astype('uint8')*255
cv2.imshow('before',img)
num, labels, stats, centroids=cv2.connectedComponentsWithStats(img,connectivity=4,ltype=cv2.CV_16U)
img=cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)

class Point():
    def __init__(self, p):
        self.x = p[0]
        self.y = p[1]

def getCircle(px1, px2, px3):
    x1 = px1.x;
    y1 = px1.y;
    x2 = px2.x;
    y2 = px2.y;
    x3 = px3.x;
    y3 = px3.y;
    e = 2 * (x2 - x1);
    f = 2 * (y2 - y1);
    g = x2*x2 - x1*x1 + y2*y2 - y1*y1;
    a = 2 * (x3 - x2);
    b = 2 * (y3 - y2);
    c = x3*x3 - x2*x2 + y3*y3 - y2*y2;
    X = (g*b - c*f) / (e*b - a*f);
    Y = (a*g - c*e) / (a*f - b*e);
    return X, Y


def bias8(p_list):
    center=np.mean(p_list,axis=0)
    vector=p_list-center
    arg=np.arctan(vector[:,1]/vector[:,0])
    p_list[np.argsort(arg)]
    arg=arg[np.argsort(arg)]
    index=list(range(len(arg)))
    index.append(index.pop(0))
    darg=(arg-arg[index])
    darg[-1]=darg[-1]-math.pi
    where=np.where(darg==np.max(darg))[0]
    p1=p_list[where,:]
    p2=p_list[index[int(where)],:]
    v=((p1+p2)/2-center)[0]
    return math.atan2(v[1],v[0])*180/math.pi+90

def bias4(p_list):
    x1,y1=getCircle(Point(p_list[0,:]),Point(p_list[1,:]),Point(p_list[2,:]))
    x2,y2=getCircle(Point(p_list[1,:]),Point(p_list[2,:]),Point(p_list[3,:]))
    center=((x1+x2)/2,(y1+y2)/2)
    vector=p_list-center
    arg=np.arctan(vector[:,1]/vector[:,0])
    p_list[np.argsort(arg)]
    arg=arg[np.argsort(arg)]
    index=list(range(len(arg)))
    index.append(index.pop(0))
    darg=(arg-arg[index])
    darg[-1]=darg[-1]-math.pi
    where=np.where(darg==np.max(darg))[0]
    return (arg[where]*180/math.pi-90)[0]

p_list=stats[1:,[0,1]]
if len(p_list)==4:
    bias=bias4(p_list)
else:
    bias=bias8(p_list)
print('偏了'+str(bias)+'度')



import numpy as np
import cv2
import math

img = cv2.imread('drop_center/img2.jpg',cv2.IMREAD_GRAYSCALE)
img=(img>128).astype('uint8')*255
#cv2.imshow('before',img)
num, labels, stats, centroids=cv2.connectedComponentsWithStats(img,connectivity=4,ltype=cv2.CV_16U)


def getPoint(area):
    points=np.where(area>0)
    center=(np.mean(p).astype(int) for p in points)
    x=np.matrix([points[0]]*len(points[0])).astype(float)
    y=np.matrix([points[1]]*len(points[1])).astype(float)
    l=np.multiply(x-x.T,x-x.T)+np.multiply(y-y.T,y-y.T)
    where=np.where(l==np.max(l))[0]
    points=(points[0][where],points[1][where])
    return center,points

theta=[]
for stat,i in zip(stats[1:],range(1,num+1)):
    area=(labels==i).astype('uint8')
    (y0,x0),((y1,y2),(x1,x2))=getPoint(area)
    if (x1-x0)**2+(y1-y0)**2>(x2-x0)**2+(y2-y0)**2:
        theta.append((np.array([x0,y0]),np.array([x2,y2]),np.array([x1,y1])))
    else:
        theta.append((np.array([x0,y0]),np.array([x1,y1]),np.array([x2,y2])))

img=cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)
for p0,p1,p2 in theta:
    #cv2.circle(img, tuple(p0), radius=10,color=(255,0,0))
    cv2.line(img, tuple(p1), tuple(p2), (0, 0, 255), int(min(img.shape)))
    cv2.circle(img, tuple(p1), int(min(img.shape)*2),(0,0,255),-1)
    t=-math.atan2((p2-p1)[1],(p2-p1)[0])*180/math.pi
    cv2.putText(img, str(t)[0:5], tuple(p0), cv2.FONT_HERSHEY_SIMPLEX, min(img.shape), (0, 255, 0), int(min(img.shape)))
    print(t)
    print(p0,p1,p2)
#cv2.imshow('after',img)
cv2.imwrite('point_to/img2.jpg',img)



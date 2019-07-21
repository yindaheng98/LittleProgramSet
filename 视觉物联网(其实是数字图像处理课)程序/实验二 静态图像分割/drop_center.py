import numpy as np
import cv2

img = cv2.imread('add/img5.jpg',cv2.IMREAD_GRAYSCALE)

#cv2.imshow('before',img)
img=(img>128).astype('uint8')*255
#cv2.imshow('before',img)
num, labels, stats, centroids=cv2.connectedComponentsWithStats(img,connectivity=4,ltype=cv2.CV_16U)
print(stats)
if len(stats)-1>8:
    p=np.mean(stats[1:,[0,1]],axis=0)
    print(p)
    length=np.sum((stats[:,[0,1]]-p)**2,axis=1)
    print(length)
    area=np.where(length==np.min(length))
    print(area)
    labels[labels==area]=0
img=(labels>0).astype('uint8')*255
#cv2.imshow('after',img)
cv2.imwrite('drop_center/img5.jpg',img)

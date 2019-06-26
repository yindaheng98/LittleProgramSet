import numpy as np
import cv2

img = cv2.imread('open_1/img2.jpg',cv2.IMREAD_GRAYSCALE)
img=(img>128).astype('uint8')*255
#img = cv2.imread('open_2/img1.jpg',cv2.IMREAD_GRAYSCALE)
#cv2.imshow('before',(img).astype('uint8'))

num, labels, stats, centroids=cv2.connectedComponentsWithStats(img,connectivity=4,ltype=cv2.CV_16U)
imga=img.shape[0]*img.shape[1]
min_thr=imga/400
max_thr=imga/150
if min(img.shape)>1900:
    min_thr=imga/895
    max_thr=imga/500
print(min_thr)
print(max_thr)
print(stats)
areas_to_drop=np.where(np.logical_or(stats[:,4]>max_thr,stats[:,4]<min_thr))
for area in areas_to_drop[0]:
    labels[labels==area]=0
img=(labels>0).astype('uint8')*255
#cv2.imshow('after',img)
cv2.imwrite('drop_1/img2.jpg',img)




import numpy as np
import cv2

#img = cv2.imread('kmeans/img1.jpg')
img = cv2.imread('kmeans/img1.jpg',cv2.IMREAD_GRAYSCALE)
cv2.imshow('l',img)
w=int(min(img.shape)/110)
kernel = np.ones((w,w),np.uint8)
img=cv2.erode(img,kernel,iterations = 1)
img=cv2.dilate(img,kernel,iterations = 1)
img=cv2.erode(img,kernel,iterations = 1)
img=cv2.dilate(img,kernel,iterations = 1)
img=cv2.morphologyEx(img,cv2.MORPH_OPEN,kernel)
#img=cv2.morphologyEx(img,cv2.MORPH_OPEN,kernel)
cv2.imshow('h',img)
cv2.imwrite('open_2/img1.jpg',img)

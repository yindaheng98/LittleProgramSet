import cv2
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread('data/img5.jpg',cv2.IMREAD_COLOR)
#cv2.imshow('before',img)
img=cv2.cvtColor(img,cv2.COLOR_BGR2YCR_CB)

Y=img[:,:,0]
Y=cv2.equalizeHist(Y)
img[:,:,0]=Y

img=cv2.cvtColor(img,cv2.COLOR_YCR_CB2BGR)
#cv2.imshow('after',img)
cv2.imwrite('equalizeHist/img5.jpg',img)

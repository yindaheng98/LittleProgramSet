import cv2
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread('msrcr/img2.jpg',cv2.IMREAD_COLOR)
#img=cv2.imread('equalizeHist/img1.jpg',cv2.IMREAD_COLOR)
img=cv2.cvtColor(img,cv2.COLOR_BGR2YCR_CB)
#cv2.imshow('before',img)
img=cv2.cvtColor(img[:,:,1],cv2.COLOR_GRAY2BGR)

cv2.imshow('after',img)
cv2.imwrite('R_channel/img2.jpg',img)


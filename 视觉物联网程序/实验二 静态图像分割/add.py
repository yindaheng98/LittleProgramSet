import numpy as np
import cv2

img1 = cv2.imread('drop_1/img1.jpg',cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread('drop_2/img1.jpg',cv2.IMREAD_GRAYSCALE)
img=np.logical_or(img1>9,img2>9).astype('uint8')*255
#cv2.imshow('after',img)
cv2.imwrite('add/img1.jpg',img)




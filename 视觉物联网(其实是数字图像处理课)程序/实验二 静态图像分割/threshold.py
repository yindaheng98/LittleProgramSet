import cv2
import numpy as np
import matplotlib.pyplot as plt

img=cv2.imread('R_channel/img5.jpg',cv2.IMREAD_GRAYSCALE)
img=(img>200).astype('uint8')*255
cv2.imshow('after',img)
cv2.imwrite('threshold/img5.jpg',img)


'''
img=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

channel=img[:,:,1]
channel=(channel-np.min(channel)).astype(int)*255/(np.max(channel)-np.min(channel))
img[:,:,1]=channel
channel=img[:,:,2]
channel=(channel-np.min(channel)).astype(int)*255/(np.max(channel)-np.min(channel))
img[:,:,2]=channel

#plt.hist(img[:,:,0])
'''
'''
Hmask=np.logical_or(img[:,:,0]>120,img[:,:,0]<10).astype('uint8')
Smask=(img[:,:,1]>40).astype('uint8')
Vmask=np.logical_or(img[:,:,2]>30,img[:,:,2]<250).astype('uint8')
mask=Hmask*Smask*Vmask
mask_3d=np.expand_dims(mask,axis=2).repeat(3,axis=2)
'''
'''
#cv2.imshow('h',img[:,:,0])
img=cv2.cvtColor(img,cv2.COLOR_HSV2BGR)
#img*=mask_3d
cv2.imshow('h',img)

'''

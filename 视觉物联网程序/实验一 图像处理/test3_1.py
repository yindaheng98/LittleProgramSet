# -*- coding:utf-8 -*-
import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.gridspec import GridSpec
from funs import plotGrayHist,grayTransform,CLAHE
from funs import img3 as img
from funs import homofilter_s as homofilter
img=cv2.medianBlur(img, 3)
img[img<50]=np.min(img[img>0])
img=CLAHE(img,2.0,(8,8))
img=((img>=0).astype(int)+(img<=100).astype(int)<2).astype('uint8')*255
'''
kernel2=np.ones((2,2),np.uint8)
kernel3=np.ones((3,3),np.uint8)
kernel4=np.ones((4,4),np.uint8)
kernel5=np.ones((5,5),np.uint8)
kernel6=np.ones((6,6),np.uint8)
'''
kernel=np.ones((12,12),np.uint8)
I=img
I=cv2.erode(img,kernel)
#cv2.imshow('hhh2',I)
I=cv2.dilate(I,kernel)
#cv2.imshow('hhh3',I)
#cv2.imwrite('3close.png',I)
Gw=np.sum(np.abs(I[:,0:-1]-I[:,1:]),axis=1)
Gh=np.sum(np.abs(I[0:-1,:]-I[1:,:]),axis=0)

Ip=I[145:391,:]
cv2.imshow('hhh',Ip[:,67:568])
'''
Gh=np.sum(np.abs(Ip[0:-1,:]-Ip[1:,:]),axis=0)
#cv2.imshow('ttt',I[145:391,:])
gs=GridSpec(4, 3)
plt.subplot(gs[0,0:3])
plt.bar(list(range(Gh.shape[0])),Gh)
plt.xlim([0,I.shape[1]])
plt.xticks([])
plt.ylabel('垂直方向差分和',fontproperties="SimHei")
plt.subplot(gs[1:4,0:3])
plt.imshow(Ip,cmap='gray')
plt.axis('off')
'''
'''
gs=GridSpec(4, 4)
plt.subplot(gs[1:4,3])
plt.barh(list(range(Gw.shape[0])),Gw)
plt.ylim([0,I.shape[0]])
plt.yticks([])
plt.xlabel('水平方向差分和',fontproperties="SimHei")
plt.subplot(gs[0,0:3])
plt.bar(list(range(Gh.shape[0])),Gh)
plt.xlim([0,I.shape[1]])
plt.xticks([])
plt.ylabel('垂直方向差分和',fontproperties="SimHei")
plt.subplot(gs[1:4,0:3])
plt.imshow(I,cmap='gray')
plt.axis('off')
'''
plt.show()
'''
I=cv2.dilate(I,kernel6)
cv2.imshow('hhh3',I)
I=cv2.dilate(I,kernel6)
cv2.imshow('hhh4',I)
'''
'''
img_mask=(img>=0).astype(int)+(img<=100).astype(int)<2
cv2.imwrite('3mask_2_1.png',img_mask.astype('uint8')*255)
img_mask=(img>=10).astype(int)+(img<=100).astype(int)<2
cv2.imwrite('3mask_2_2.png',img_mask.astype('uint8')*255)
img_mask=(img>=20).astype(int)+(img<=100).astype(int)<2
cv2.imwrite('3mask_2_3.png',img_mask.astype('uint8')*255)
img_mask=(img>=30).astype(int)+(img<=100).astype(int)<2
cv2.imwrite('3mask_2_4.png',img_mask.astype('uint8')*255)
'''
'''
img_mask=(img>=0).astype(int)+(img<=60).astype(int)<2
cv2.imwrite('3mask_1_1.png',img_mask.astype('uint8')*255)
img_mask=(img>=0).astype(int)+(img<=80).astype(int)<2
cv2.imwrite('3mask_1_2.png',img_mask.astype('uint8')*255)
img_mask=(img>=0).astype(int)+(img<=100).astype(int)<2
cv2.imwrite('3mask_1_3.png',img_mask.astype('uint8')*255)
img_mask=(img>=0).astype(int)+(img<=120).astype(int)<2
cv2.imwrite('3mask_1_4.png',img_mask.astype('uint8')*255)
'''
#cv2.imshow('hhh2',img_mask.astype('uint8')*255)
'''
img[img<50]=np.min(img[img>0])
img_clahe=CLAHE(img,2.0,(8,8))
cv2.imshow('hhh',img_clahe)
cv2.imwrite('3_img_clahe_2.png',img_clahe)
plt.figure(figsize=(8,8),dpi=64)
plotGrayHist(img_clahe)
#plt.show()
plt.savefig('3_img_clahe_2.pdf')
'''
'''
img_homo=homofilter(img,rL,rH,c,d0)
#plotGrayHist(img_homo[img_homo>0])
img_eqhist=CLAHE(img_homo,4.0,(4,4))
plotGrayHist(img_eqhist[img_eqhist>0])
plt.show()
'''
'''
cv2.imwrite('2_clip_limit_2.png',CLAHE(img_homo,2.0,(8,8)))
cv2.imwrite('2_clip_limit_3.png',CLAHE(img_homo,3.0,(8,8)))
cv2.imwrite('2_clip_limit_4.png',CLAHE(img_homo,4.0,(8,8)))
cv2.imwrite('2_clip_limit_5.png',CLAHE(img_homo,5.0,(8,8)))

cv2.imwrite('2_tile_grid_size_4.png',CLAHE(img_homo,3.0,(4,4)))
cv2.imwrite('2_tile_grid_size_8.png',CLAHE(img_homo,3.0,(8,8)))
cv2.imwrite('2_tile_grid_size_12.png',CLAHE(img_homo,3.0,(12,12)))
cv2.imwrite('2_tile_grid_size_16.png',CLAHE(img_homo,3.0,(16,16)))
'''


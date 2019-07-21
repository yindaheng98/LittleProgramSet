# -*- coding:utf-8 -*-
import cv2
import numpy as np
import matplotlib.pyplot as plt
from funs import img2,plotGrayHist,grayTransform,CLAHE,homofilter
from funs import img2 as img
from funs import homofilter as homofilter
#cv2.imshow('h',img)


rL=0.5
rH=4
c=3.5
d0=3
img_homo=homofilter(img,rL,rH,c,d0)
cv2.imwrite('2homo.png',img_homo)
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
'''
cv2.imwrite('2_tile_grid_size_4.png',CLAHE(img_homo,3.0,(4,4)))
cv2.imwrite('2_tile_grid_size_8.png',CLAHE(img_homo,3.0,(8,8)))
cv2.imwrite('2_tile_grid_size_12.png',CLAHE(img_homo,3.0,(12,12)))
cv2.imwrite('2_tile_grid_size_16.png',CLAHE(img_homo,3.0,(16,16)))
'''
plt.subplot(1,2,1)
plt.imshow(img,cmap='gray')
plt.axis('off')
plt.title(u'原图',fontproperties="SimHei",fontsize=20)

plt.subplot(1,2,2)
img_homo=homofilter(img,rL,rH,c,d0)
plt.imshow(img_homo,cmap='gray')
plt.axis('off')
plt.title(u'同态滤波结果',fontproperties="SimHei",fontsize=20)
'''
'''
plt.subplot(1,3,1)
plt.imshow(img,cmap='gray')
plt.axis('off')
plt.title('原图',fontproperties="SimHei",fontsize=20)

plt.subplot(1,3,2)
img_homo=homofilter(img,rL,rH,c,d0)
plt.imshow(img_homo,cmap='gray')
plt.axis('off')
plt.title('同态滤波结果',fontproperties="SimHei",fontsize=20)

plt.subplot(1,3,3)
img_corr=CLAHE(img_homo,2.0,(16,16))
plt.imshow(img_corr,cmap='gray')
plt.axis('off')
plt.title('CLAHE结果',fontproperties="SimHei",fontsize=20)
'''
'''
plt.subplot(2,3,1)
plt.imshow(img,cmap='gray')
plt.title('原图',fontproperties="SimSun")

plt.subplot(2,3,2)
img_homo=homofilter(img,rL,rH,c,d0)
plt.imshow(img_homo,cmap='gray')
plt.title('同态滤波结果',fontproperties="SimSun")

plt.subplot(2,3,3)
img_eqhist=CLAHE(img,4.0,(4,4))
plt.imshow(img_eqhist,cmap='gray')
plt.title('CLAHE')

plt.subplot(2,3,4)
img_homo_eqhist=CLAHE(img_homo,4.0,(4,4))
plt.imshow(img_homo_eqhist,cmap='gray')
plt.title('Homofilter->CLAHE')


plt.subplot(2,3,5)
img_eqhist_homo=homofilter(img_eqhist,rL,rH,c,d0)
plt.imshow(img_eqhist_homo,cmap='gray')
plt.title('CLAHE->Homofilter')
'''
#img_homo=homofilter(img,rL,rH,c,d0)

'''
plt.subplot(1,4,1)
plt.imshow(CLAHE(img_homo,2.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=2',fontsize=25)
plt.subplot(1,4,2)
plt.imshow(CLAHE(img_homo,3.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=3',fontsize=25)
plt.subplot(1,4,3)
plt.imshow(CLAHE(img_homo,4.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=4',fontsize=25)
plt.subplot(1,4,4)
plt.imshow(CLAHE(img_homo,5.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=5',fontsize=25)
'''
'''
plt.subplot(1,4,1)
plt.imshow(CLAHE(img_homo,2,(4,4)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=4',fontsize=25)
plt.subplot(1,4,2)
plt.imshow(CLAHE(img_homo,2,(8,8)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=8',fontsize=25)
plt.subplot(1,4,3)
plt.imshow(CLAHE(img_homo,2,(12,12)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=12',fontsize=25)
plt.subplot(1,4,4)
plt.imshow(CLAHE(img_homo,2,(16,16)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=16',fontsize=25)
'''
plt.show()


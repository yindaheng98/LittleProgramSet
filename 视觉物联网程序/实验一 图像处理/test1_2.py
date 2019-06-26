import cv2
import numpy as np
import matplotlib.pyplot as plt
from funs import img1,plotGrayHist,grayTransform,CLAHE

#cv2.imshow('h',img1)

plotGrayHist(CLAHE(img1,2.0,(8,8)))

#img1_eqhist=cv2.equalizeHist(img1)

img1_eqhist=CLAHE(img1,4.0,(4,4))
#plt.axis('off')
#plt.imshow(img1_eqhist,cmap='gray')
#img1_eqhist=(255.0*(img1-np.min(img1))/(np.max(img1)-np.min(img1))).astype('uint8')
#cv2.imwrite('CLAHE4.png',img1_eqhist)

#cv2.imwrite('norm.png',grayTransform(img1,lambda x:x))
'''
cv2.imwrite('1_clip_limit_2.png',CLAHE(img1,2.0,(8,8)))
cv2.imwrite('1_clip_limit_3.png',CLAHE(img1,3.0,(8,8)))
cv2.imwrite('1_clip_limit_4.png',CLAHE(img1,4.0,(8,8)))
cv2.imwrite('1_clip_limit_5.png',CLAHE(img1,5.0,(8,8)))
'''
'''
cv2.imwrite('1_tile_grid_size_4.png',CLAHE(img1,2.0,(4,4)))
cv2.imwrite('1_tile_grid_size_8.png',CLAHE(img1,2.0,(8,8)))
cv2.imwrite('1_tile_grid_size_12.png',CLAHE(img1,2.0,(12,12)))
cv2.imwrite('1_tile_grid_size_16.png',CLAHE(img1,2.0,(16,16)))
'''
'''
plt.subplot(1,4,1)
plt.imshow(CLAHE(img1,2.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=2',fontsize=25)
plt.subplot(1,4,2)
plt.imshow(CLAHE(img1,3.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=3',fontsize=25)
plt.subplot(1,4,3)
plt.imshow(CLAHE(img1,4.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=4',fontsize=25)
plt.subplot(1,4,4)
plt.imshow(CLAHE(img1,5.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('clip limit=5',fontsize=25)
'''
'''
plt.subplot(1,4,1)
plt.imshow(CLAHE(img1,4.0,(4,4)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=4',fontsize=25)
plt.subplot(1,4,2)
plt.imshow(CLAHE(img1,4.0,(8,8)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=8',fontsize=25)
plt.subplot(1,4,3)
plt.imshow(CLAHE(img1,4.0,(12,12)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=12',fontsize=25)
plt.subplot(1,4,4)
plt.imshow(CLAHE(img1,4.0,(16,16)),cmap='gray')
plt.axis('off')
plt.title('tile grid size=16',fontsize=25)
'''
#img1_eqhist=grayTransform(img1,lambda img:np.power(img/255.0,2)*255.0)
'''
plt.subplot(1,2,1)
plt.imshow(img1_eqhist,cmap='gray')
plt.axis('off')
plt.subplot(1,2,2)
plotGrayHist(img1_eqhist)
'''
plt.show()

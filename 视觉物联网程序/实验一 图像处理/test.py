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
#cv2.imwrite('3maskcut.png',img[145:391,67:568])
img=img[145:391,67:568]
_, contours, hierarchy=cv2.findContours(img,cv2.RETR_TREE,cv2.CHAIN_APPROX_NONE)
areas=np.array([cv2.contourArea(cnt) for cnt in contours])
contours=np.array(contours)[areas.argsort()]
img=cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)


cv2.drawContours(img, contours[-19:-1], -1, (0,0,255), 2)



    
cv2.imwrite('3maskcut_sel.png',img)

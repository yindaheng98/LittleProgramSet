import cv2
import matplotlib.pyplot as plt
from RGB import channel as RGBchannel
from RGB import t as RGBt
from RGB import dat as RGBdat
from HSV import channel as HSVchannel
from HSV import t as HSVt
from HSV import dat as HSVdat
t_str='t%d.jpg'
for i in range(2):
    img=cv2.imread(t_str%(i+1),cv2.IMREAD_COLOR)
    plt.subplot(2,3,3*i+1)
    plt.title(u'原图',fontproperties="SimHei")
    plt.axis('off')
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    
    img=RGBt[i]
    plt.subplot(2,3,3*i+2)
    plt.title(u'RGB颜色空间内的掩膜结果'
          ,fontproperties="SimHei")
    plt.axis('off')
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
    
    img=HSVt[i]
    plt.subplot(2,3,3*i+3)
    plt.title(u'HSV颜色空间内的掩膜结果'
          ,fontproperties="SimHei")
    plt.axis('off')
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_HSV2RGB))
plt.savefig('res1.png', dpi=600)
'''
plt.figure(figsize=(20,10))
plt.subplot(1,2,1)
labs=['Blue','Green','Red']
clr=['b','g','r']
for c in range(RGBchannel):
    plt.plot(RGBdat[c][0],RGBdat[c][1],label=labs[c],color=clr[c])
plt.title(u'RGB颜色空间内样本区域像素颜色分量数值数量对应关系'
          ,fontproperties="SimHei")
plt.xlabel(u'数值',fontproperties="SimHei")
plt.ylabel(u'数量',fontproperties="SimHei")
plt.legend(loc='upper left')
plt.subplot(1,2,2)
labs=['Hue','Saturation','Value']
for c in range(HSVchannel):
    plt.plot(HSVdat[c][0],HSVdat[c][1],label=labs[c])
plt.title(u'HSV颜色空间内样本区域像素颜色分量数值数量对应关系'
          ,fontproperties="SimHei")
plt.xlabel(u'数值',fontproperties="SimHei")
plt.ylabel(u'数量',fontproperties="SimHei")
plt.legend(loc='upper right')
plt.savefig('res2.png')
'''

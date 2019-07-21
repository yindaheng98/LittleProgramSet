import cv2
import matplotlib.pyplot as plt
t_str='t%d.jpg'
i=0
img=cv2.imread(t_str%(i+1),cv2.IMREAD_COLOR)
plt.subplot(2,3,2*i+1)
plt.title(u'原图',fontproperties="SimHei")
plt.axis('off')
plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.show()

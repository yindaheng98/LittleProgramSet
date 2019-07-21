import cv2
import matplotlib.pyplot as plt
import numpy as np

tr=[]
tr_str='tr%d.jpg'
for i in range(0,4):
    tr.append(cv2.imread(tr_str%(i+1),cv2.IMREAD_COLOR))
    #cv2.imshow(tr_str%(i+1),tr[i])

tr_p=[]
tr_p.append(((480,150),(450,320)))
tr_p.append(((880,50),(700,320)))
tr_p.append(((580,50),(330,400)))
tr_p.append(((300,180),(400,400)))
w,h=100,100
tr_smp=[]

'''
for i in range(0,4):
    ((x1,y1),(x2,y2))=tr_p[i]
    img=tr[i]
    img=cv2.rectangle(img, (x1,y1),(x1+w,y1+h), (0,0,255), 2)
    img=cv2.rectangle(img, (x2,y2),(x2+w,y2+h), (0,0,255), 2)
    plt.subplot(2,2,i+1)
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.savefig('spa.png', dpi=600)
'''

for i in range(0,4):
    ((x1,y1),(x2,y2))=tr_p[i]
    img=tr[i]
    tr_smp.append(img[y1:y1+h,x1:x1+w,:])
    tr_smp.append(img[y2:y2+h,x2:x2+w,:])
'''
for i in range(0,8):
    plt.subplot(2,4,i+1)
    plt.imshow(cv2.cvtColor(tr_smp[i], cv2.COLOR_BGR2RGB))
plt.savefig('sp.png', dpi=600)
'''
channel=tr_smp[0].shape[-1]
dat=[]
for c in range(channel):
    d=np.array(np.zeros([0,1]))
    for tr_s in tr_smp:
        d=np.concatenate((d,tr_s[:,:,c].reshape((-1,1))),axis=0)
    d=np.unique(d, return_counts=True)
    dat.append(d)
'''
for c in range(channel):
    plt.plot(dat[c][0],dat[c][1])
plt.show()
'''
ranges=[]
for c in range(channel):
    tops=dat[c][0][np.argsort(-dat[c][1])][0:100]
    ranges.append([np.min(tops),np.max(tops)])

t=[]
t_str='t%d.jpg'
for i in range(2):
    t.append(cv2.imread(t_str%(i+1),cv2.IMREAD_COLOR))
    #cv2.imshow(t_str%(i+1),t[i])

for i in range(2):
    img=t[i]
    mask=np.array([[True]*img.shape[1]]*img.shape[0])
    for c in range(channel):
        mask*=(img[:,:,c]>=ranges[c][0])*(img[:,:,c]<=ranges[c][1])
    t[i][~mask]=[0,0,0]
'''
for i in range(2):
    img=t[i]
    plt.subplot(1,2,i+1)
    plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
plt.savefig('res.png', dpi=600)
'''

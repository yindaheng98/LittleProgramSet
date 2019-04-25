import cv2
import numpy as np
from grid import xcenter,ycenter,dx,dy,xrange,yrange,img

img=img[xcenter+dx*xrange[0]:xcenter+dx*xrange[1],
        ycenter+dy*yrange[0]:ycenter+dy*yrange[1]]
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

Lower = np.array([0, 30, 30])#要识别颜色的下限
Upper = np.array([20, 200, 200])#要识别的颜色的上限
mask = cv2.inRange(hsv, Lower, Upper)
Lower[0] = 160
Upper[0] = 180
mask += cv2.inRange(hsv, Lower, Upper)
Lower = np.array([20, 100, 100])#要识别颜色的下限
Upper = np.array([40, 255, 255])#要识别的颜色的上限
mask += cv2.inRange(hsv, Lower, Upper)

print(mask.shape)
#测试
#cv2.imshow('hhh',mask)

nx=xrange[1]-xrange[0]
ny=yrange[1]-yrange[0]
roads=np.zeros([nx,ny])
for i in range(dx):
    for j in range(dy):
        roads+=mask[i::dx,j::dy]
roads/=dx*dy*255

kernel=np.ones([3,3])
roads=cv2.filter2D(roads,-1,kernel)
roads/=9

def roadfill(how_much):
    top_thr=np.sort(roads.reshape(-1))[::-1][how_much]
    print(roads.shape)
    top_locs=np.argwhere(roads>top_thr)
    print(top_locs)

    for top_loc in top_locs:
        print((top_loc[0]*dx,top_loc[1]*dy),(top_loc[0]*dx+dx,top_loc[1]*dy+dy))
        cv2.rectangle(img,
                      (top_loc[1]*dy,top_loc[0]*dx),
                      (top_loc[1]*dy+dy,top_loc[0]*dx+dx),
                      (0, 255, 0),
                      -1)
    print(img.shape)
    cv2.imwrite('roadfill'+str(how_much)+'.png',img)



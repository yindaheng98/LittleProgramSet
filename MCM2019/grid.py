import cv2
import numpy as np
import math
img = cv2.imread('pic.png', cv2.IMREAD_COLOR)
hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

xcenter,ycenter=(525,401)
dx,dy=(70,66)
xrange=(-6,1)
yrange=(-3,17)

scale=1
dx=math.floor(dx/scale)
dy=math.floor(dy/scale)
xrange=tuple([xr*scale for xr in xrange])
yrange=tuple([yr*scale for yr in yrange])

#画中心
img[xcenter,ycenter,:]=[0,0,255]
img[xcenter,:,:]=[0,0,255]
img[:,ycenter,:]=[0,0,255]

#画x方向网格
img[xcenter+dx*xrange[0]:xcenter:dx,:,:]=[0,0,255]
img[xcenter:xcenter+dx*xrange[1]+dx:dx,:,:]=[0,0,255]

#画y方向网格
img[:,ycenter+dy*yrange[0]:ycenter:dy,:]=[0,0,255]
img[:,ycenter:ycenter+dy*yrange[1]+dy:dy,:]=[0,0,255]

#cv2.imshow('hhh',img)
cv2.imwrite('grid.png',img)

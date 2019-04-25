# -*- coding: cp936 -*-
import cv2
from numpy import *
# 设置视频捕获
cap = cv2.VideoCapture(0)
frames = []
i=0
# 获取帧，存储到数组中
font=cv2.FONT_HERSHEY_SIMPLEX
while True:
  ret,frame = cap.read()
  gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
  gray = cv2.GaussianBlur(gray,(3,3),0)
  canny=cv2.Canny(gray,50,150)
  #cv2.imshow('video',gray)
  frames.append(canny)
  if i==0:
    i+=1
    continue
  diff=frames[i]-frames[i-1]
  jingzhi=sum(((diff!=0)+0).reshape(1,-1))
  zhedang=sum(((frames[i-1]!=0)+0).reshape(1,-1))
  if zhedang<8000:
    cv2.putText(canny,'zhedang',(10,40), font, 2,(255,255,255),2)
  if jingzhi==0:
    cv2.putText(canny,str(jingzhi),(10,80), font, 2,(255,255,255),2)
  cv2.imshow('video',canny)
  cv2.waitKey(25)
  i+=1
  if cv2.waitKey(1) & 0xFF == ord('q'):
    break
cap.release()
cv2.destroyAllWindows()

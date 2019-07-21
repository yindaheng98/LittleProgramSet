# -*- coding: utf-8 -*-
import cv2
import numpy as np

D=50#在此调节差多少帧
#fname='mixture_of_gaussians_output.avi'
#fname='帧差1.avi'
#save_name='sb1'
#fname='时间平均49.avi'
#save_name='avg49'
fname='单高斯N80.avi'
save_name='single_gN80'
cap = cv2.VideoCapture(fname)

d=0
frames=[]
fnum=0
while(1):
    ret, frame = cap.read()
    if (cv2.waitKey(1) & 0xFF == ord('q')) or not ret:
        break
    cv2.imshow("frame", frame)
    fnum+=1
#    if fnum==400 or fnum==405 or fnum==410 or fnum==415:
    if fnum==340 or fnum==345 or fnum==350 or fnum==355:
        cv2.imwrite('frames/'+save_name+str(fnum)+'.jpg',frame)

cap.release()
cv2.destroyAllWindows()

import cv2
from numpy import *

cap = cv2.VideoCapture(0)
ret,im = cap.read()
gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
font=cv2.FONT_HERSHEY_SIMPLEX
while True:
    ret,im = cap.read()
    gray = cv2.cvtColor(im,cv2.COLOR_BGR2GRAY)
    cv2.waitKey(25)
    score = gray.mean()
    score1 = gray.var()
    cv2.putText(gray,str(round(score,2)),(10,50), font, 2,(255,255,255),2)
    cv2.putText(gray,str(round(score1,2)),(10,100), font, 2,(255,255,255),2)
    cv2.imshow('lalala',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

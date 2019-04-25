import cv2
from numpy import *

cap = cv2.VideoCapture(0)
ret, im = cap.read()
LABImg = cv2.cvtColor(im, cv2.COLOR_BGR2LAB)
font = cv2.FONT_HERSHEY_SIMPLEX
while True:
    ret, im = cap.read()
    LABImg = cv2.cvtColor(im, cv2.COLOR_BGR2LAB)
    cv2.waitKey(25)
    L, A, B = cv2.split(LABImg)
    score = A.mean()
    score1 = A.var()
    score2 = B.mean()
    score3 = B.var()
    cv2.putText(im, str(round(score, 2)), (10, 50), font, 2, (255, 255, 255), 2)
    cv2.putText(im, str(round(score1, 2)), (10, 100), font, 2, (255, 255, 255), 2)
    cv2.putText(im, str(round(score2, 2)), (300, 50), font, 2, (255, 255, 255), 2)
    cv2.putText(im, str(round(score3, 2)), (300, 100), font, 2, (255, 255, 255), 2)
    cv2.imshow('lalala', im)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

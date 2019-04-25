# -*- coding: cp936 -*-
import numpy as np
import cv2

cap = cv2.VideoCapture(0)
font = cv2.FONT_HERSHEY_SIMPLEX
ret, img1 = cap.read()
cv2.imwrite('d.png', img1)
#img1 = cv2.imread('H:/python/guangliu.py/c.jpg',0) #初始化视角
while True:
    ret, frame = cap.read()

    cv2.waitKey(25)

    sift = cv2.xfeatures2d.SIFT_create()
    kp1, des1 = sift.detectAndCompute(img1, None)
    kp2, des2 = sift.detectAndCompute(frame, None)

    # BFMatcher with default params
    bf = cv2.BFMatcher()
    matches = bf.knnMatch(des1, des2, k=2)
    good = []
    for m, n in matches:
        if m.distance < 0.75 * n.distance:
            good.append([m])
    cv2.putText(frame, str(len(good)), (10, 80), font, 2, (255, 255, 255), 2)  # 小于一定的值
    cv2.imshow('video', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

import numpy as np
import cv2

cap = cv2.VideoCapture(0)
i=0
# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*'XVID')
out = cv2.VideoWriter('output.avi',fourcc, 20.0, (640,480))

while(cap.isOpened()):
    ret, im = cap.read()
    if ret==True:
        if i==1:
            im= cv2.GaussianBlur(im,(0,0),5)
        out.write(im)
        cv2.imshow('frame',im)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        if cv2.waitKey(1) & 0xFF == ord(' '):
            if i%2==0:
                i=1
            else:
                i=0
    else:
        break

# Release everything if job is finished
cap.release()
out.release()
cv2.destroyAllWindows()

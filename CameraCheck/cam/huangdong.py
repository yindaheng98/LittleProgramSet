import cv2
from numpy import *
import math



def draw_flow(im, flow, step=16):
    h, w = im.shape[:2]
    y, x = mgrid[step / 2:h:step, step / 2:w:step].reshape(2, -1)
    fx, fy = flow[y.astype('int32'), x.astype('int32')].T

    lines = vstack([x, y, x + fx, y + fy]).T.reshape(-1, 2, 2)
    lines = int32(lines)
    xxx = 0
    vis = cv2.cvtColor(im, cv2.COLOR_GRAY2BGR)
    for (x1, y1), (x2, y2) in lines:
        #cv2.line(vis,(x1,y1),(x2,y2),(0,255,0),1)
        xxx = xxx + x2 - x1
        #cv2.circle(vis,(x1,y1),1,(0,255,0), -1)
    return vis, xxx



cap = cv2.VideoCapture(0)
ret, im = cap.read()
prev_gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
font = cv2.FONT_HERSHEY_SIMPLEX
xxx = 0
while True:
    ret, im = cap.read()
    gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    cv2.waitKey(25)
    flow = cv2.calcOpticalFlowFarneback(prev_gray, gray, None, 0.5, 3, 15, 3, 5, 1.2, 0)
    prev_gray = gray
    vis, xxx = draw_flow(gray, flow)
    if xxx < 0:
        xxx = -xxx
    if xxx > 2000:
        cv2.putText(vis, 'shake', (400, 50), font, 2, (255, 255, 255), 2)
    cv2.putText(vis, str(int64(xxx)), (10, 50), font, 2, (255, 255, 255), 2)
    cv2.imshow('Optical flow', vis)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

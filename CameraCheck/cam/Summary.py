import cv2
import math
import numpy as np

videoCapture = cv2.VideoCapture()
videoCapture.open(0)
fps = videoCapture.get(cv2.CAP_PROP_FPS)
font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX
success = True
while success:
    success, frame = videoCapture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)




videoCapture.release()
cv2.destroyAllWindows()
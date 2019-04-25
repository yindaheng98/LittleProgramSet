import cv2
import numpy as np

videoCapture = cv2.VideoCapture()
videoCapture.open(0)
fps = videoCapture.get(cv2.CAP_PROP_FPS)
font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX
success = True
while success:
    success, frame = videoCapture.read()
    copy = frame[:, :, [0, 1, 2]]
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    B = copy[:, :, 0]
    G = copy[:, :, 1]
    R = copy[:, :, 2]

    cv2.imshow('img', frame)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break
videoCapture.release()
cv2.destroyAllWindows()

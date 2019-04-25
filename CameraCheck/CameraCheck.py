import cv2
from CheckFunctions.Check import Check

videoCapture = cv2.VideoCapture()
videoCapture.open(0)
fps = videoCapture.get(cv2.CAP_PROP_FPS)
font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX
success = True
while success:
    success, frame = videoCapture.read()
    cv2.imshow('frame', frame)
    print(Check(frame))
videoCapture.release()
cv2.destroyAllWindows()

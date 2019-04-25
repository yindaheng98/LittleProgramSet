import cv2
import numpy as np

videoCapture = cv2.VideoCapture()
videoCapture.open(0)
fps = videoCapture.get(cv2.CAP_PROP_FPS)
font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX
success = True
while success:
    success, frame = videoCapture.read()

    edges = cv2.Canny(frame, 100, 100)
    sum = np.sum(((edges != 0) + 0).reshape(1, -1))
    x, y = edges.shape
    sum = sum / (x * y)
    cv2.putText(frame, str(sum), (0, 100), font, 1, (255, 255, 255))
    cv2.imshow('img', frame)
    cv2.imshow('edges', edges)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break
videoCapture.release()
cv2.destroyAllWindows()

'''
img=np.zeros([400,800,3])
img=cv2.Canny(img,100,200)
sum=np.sum(((img!=0)+255).reshape(1,-1))
print(sum)
'''

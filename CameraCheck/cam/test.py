import cv2
import math
import numpy as np



def var(matrix, dx, dy):
    x, y = matrix.shape
    x = math.floor(x / dx)
    y = math.floor(y / dy)
    z = dx * dy
    submat = np.ndarray([x, y, z])
    for i in range(0, dx):
        for j in range(0, dy):
            m = matrix[i::dx, j::dy]
            submat[:, :, i * dy + j] = m[0:x, 0:y]
    return submat.var(axis=2)



videoCapture = cv2.VideoCapture()
videoCapture.open(0)
fps = videoCapture.get(cv2.CAP_PROP_FPS)
font = cv2.FONT_HERSHEY_SCRIPT_SIMPLEX
success = True
while success:
    success, frame = videoCapture.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    v = var(gray, 2, 2)
    cv2.imshow('var', v)
    x, y = v.shape
    varsum = np.sum(v.reshape(1, -1)) / (x * y)
    cv2.putText(gray, str(varsum), (0, 100), font, 1, (255, 255, 255))

    cv2.imshow('img', gray)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break
videoCapture.release()
cv2.destroyAllWindows()

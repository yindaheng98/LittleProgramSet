import cv2
import math
import numpy as np



def conv(matrix, kernel):
    dx, dy = kernel.shape
    x, y = matrix.shape
    x = np.floor(x / dx).astype(int)
    y = np.floor(y / dy).astype(int)
    submat = np.zeros([x, y])
    for i in range(0, dx):
        for j in range(0, dy):
            m = matrix[i::dx, j::dy]
            submat = submat + kernel[i, j] * m[0:x, 0:y]
    return submat



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

    k = np.matrix([[0.25, 0, 0.25], [0, 0, 0], [0.25, 0, 0.25]])
    c = conv(gray, k).astype(float)
    cv2.imshow('conv', c)
    print('c=')
    print(c[0, 0])

    cv2.imshow('img', frame)
    if cv2.waitKey(25) & 0xFF == ord('q'):
        break
videoCapture.release()
cv2.destroyAllWindows()

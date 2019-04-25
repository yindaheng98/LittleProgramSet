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



def zaodian(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    v = var(gray, 2, 2)
    x, y = v.shape
    varsum = np.sum(v.reshape(1, -1)) / (x * y)
    return varsum

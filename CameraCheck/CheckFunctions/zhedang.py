import cv2
import numpy as np



def zhedang(frame):
    edges = cv2.Canny(frame, 100, 100)
    s = np.sum(((edges != 0) + 0).reshape(1, -1))
    return s

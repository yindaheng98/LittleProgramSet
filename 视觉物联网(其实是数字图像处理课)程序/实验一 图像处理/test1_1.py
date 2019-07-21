import cv2
import numpy as np
import matplotlib.pyplot as plt
from funs import img1,plotGrayHist,grayTransform,CLAHE,homofilter

img1_eqhist=(255.0*(img1-np.min(img1))/(np.max(img1)-np.min(img1))).astype('uint8')
cv2.imshow('hh',img1_eqhist)

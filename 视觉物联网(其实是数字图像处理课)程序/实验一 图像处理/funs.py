import cv2
import numpy as np
import matplotlib.pyplot as plt

img1=cv2.imread('image1.bmp',cv2.IMREAD_GRAYSCALE)
img2=cv2.imread('image2.jpg',cv2.IMREAD_GRAYSCALE)
img3=cv2.imread('image3.tif',cv2.IMREAD_GRAYSCALE)
img4=cv2.imread('image4.tif',cv2.IMREAD_GRAYSCALE)

def plotGrayHist(img):#画灰度直方图
    gray_hist=cv2.calcHist([img],channels=[0], mask=None,
                           histSize=[256],
                           ranges=[0,255]).reshape((-1))
    plt.bar(list(range(gray_hist.shape[0])),gray_hist)
    plt.tick_params(labelsize=20)

def grayTransform(img,fun):#灰度变换
    I=fun(img.astype(float))
    I=(255*(I-np.min(I))/(np.max(I)-np.min(I))).astype('uint8')
    return I

def CLAHE(img,clipLimit,tileGridSize):#CLAHE
    clahe= cv2.createCLAHE(clipLimit=clipLimit,
                           tileGridSize=tileGridSize) #定义CLAHE
    I=clahe.apply(img).astype(float)
    I=(255*(I-np.min(I))/(np.max(I)-np.min(I))).astype('uint8')
    return I

def homofilter_abstract(I,fH):
    I = np.double(I)
    m,n = I.shape
    n1 = np.floor(m/2)
    n2 = np.floor(n/2)
    I = np.log(I+1)
    I = np.fft.fft2(I)
    #I = np.fft.fftshift(I)
    D = np.zeros((m,n))
    H = np.zeros((m,n))
    for i in range(m):
        for j in range(n):
            D=((i-n1)**2+(j-n2)**2)
            H[i,j]=fH(D)
    I = H*I
    #I = np.fft.ifftshift(I)
    I = np.fft.ifft2(I)
    I = np.real(np.exp(I))
    I=(255*(I-np.min(I))/(np.max(I)-np.min(I))).astype('uint8')
    return I

def H1(D,rL,rH,c,d0):
    return (rH-rL)*(np.exp(-c*D/d0))+rL

def H0(D,rL,rH,c,d0):
    return (rH-rL)*(1-np.exp(-c*D/d0**2))+rL

def homofilter(I,rL,rH,c,d0):
    return homofilter_abstract(I,lambda D:H1(D,rL,rH,c,d0))

def homofilter_s(I):   
    rL=0.5
    rH=4
    c=3.5
    d0=3
    return homofilter_abstract(I,lambda D:H1(D,rL,rH,c,d0))

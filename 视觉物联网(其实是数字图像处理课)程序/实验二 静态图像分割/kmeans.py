import numpy as np
import cv2

img = cv2.imread('MSRCR/img2.jpg')
Z = img.reshape((-1,3))

# convert to np.float32
Z = np.float32(Z)

# define criteria, number of clusters(K) and apply kmeans()
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 10, 1.0)
K = 4
ret,label,center=cv2.kmeans(Z,K,None,criteria,10,cv2.KMEANS_RANDOM_CENTERS)

# Now convert back into uint8, and make original image
center = np.uint8(center)
res = center[(label.flatten()<1).astype(int)]
res2 = res.reshape((img.shape))

cv2.imshow('res2',res2)

img=cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

cv2.imshow('GRAY',img)

img=(img<75).astype('uint8')*255

cv2.imshow('img',img)
cv2.imwrite('kmeans/img2.jpg',img)

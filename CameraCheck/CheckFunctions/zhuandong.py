import cv2
import CheckFunctions.global_frame as gf



def zhuandong(frame):
    if gf.frame0 == []:
        gf.frame0 = frame
    sift = cv2.xfeatures2d.SIFT_create()
    kp1, des1 = sift.detectAndCompute(gf.frame0, None)
    kp2, des2 = sift.detectAndCompute(frame, None)

    # BFMatcher with default params
    bf = cv2.BFMatcher()
    matches = bf.knnMatch(des1, des2, k=2)
    good = []
    for m, n in matches:
        if m.distance < 0.75 * n.distance:
            good.append([m])
    return len(good)

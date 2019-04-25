import cv2



def mohu(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    cv2.waitKey(25)
    score = cv2.Laplacian(gray, cv2.CV_64F).var()
    return score

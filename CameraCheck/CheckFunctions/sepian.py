import cv2



def sepian(frame):
    LABImg = cv2.cvtColor(frame, cv2.COLOR_BGR2LAB)
    cv2.waitKey(25)
    L, A, B = cv2.split(LABImg)
    score1 = A.var()
    score3 = B.var()
    return [score1, score3]

import cv2



def liangdu(frame):
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    score = gray.mean()
    score1 = gray.var()
    return [score, score1]

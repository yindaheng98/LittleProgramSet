import cv2

cap = cv2.VideoCapture(0)
ret, im = cap.read()
gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
font = cv2.FONT_HERSHEY_SIMPLEX
while True:
    ret, im = cap.read()
    gray = cv2.cvtColor(im, cv2.COLOR_BGR2GRAY)
    cv2.waitKey(25)
    score = cv2.Laplacian(gray, cv2.CV_64F).var()
    if score < 50:
        cv2.putText(gray, 'not clear', (10, 50), font, 2, (255, 255, 255), 2)
    cv2.imshow('Optical flow', gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()

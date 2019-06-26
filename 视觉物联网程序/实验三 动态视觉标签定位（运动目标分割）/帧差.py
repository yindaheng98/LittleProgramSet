import cv2
import numpy as np

D=5#在此调节差多少帧

cap = cv2.VideoCapture("raw.avi")
#cap = cv2.VideoCapture(0)
videoWriter = cv2.VideoWriter(
    '帧差%d.avi'%(D-1),
    cv2.VideoWriter_fourcc(*'XVID'),
    cap.get(cv2.CAP_PROP_FPS),
    (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
     int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))))
print(cap.get(cv2.CAP_PROP_FPS),
    (int(cap.get(cv2.CAP_PROP_FRAME_WIDTH)),
     int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))))

d=0
frames=[]
while(1):
    ret, frame = cap.read()
    if (cv2.waitKey(1) & 0xFF == ord('q')) or not ret:
        break
    d+=1

    frame=cv2.cvtColor(frame,cv2.COLOR_BGR2GRAY)
    frames.append(frame)
    if d<D:
        continue
    last_frame=frames.pop(0)
    df=frame-last_frame
    df=(df>100).astype('uint8')*255
    videoWriter.write(cv2.cvtColor(df,cv2.COLOR_GRAY2BGR))
    cv2.imshow("df", df)
    cv2.imshow("frame", frame)
    cv2.imshow("last_frame", last_frame)

videoWriter.release()
cap.release()
cv2.destroyAllWindows()

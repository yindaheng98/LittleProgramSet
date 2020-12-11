#!/usr/bin/env python
# -*-coding:utf-8-*-
import cv2
import os

root = os.path.split(__file__)[0]

img_dir = os.path.join(root, "selected")
list_image = os.listdir(img_dir)
list_image.sort()
list_image = [os.path.join(img_dir,x) for x in list_image]
print(list_image)

video_path = os.path.join(root, '合成.mp4')
fsp = 4
fourcc = cv2.VideoWriter_fourcc('D', 'I', 'V', 'X')
width = cv2.imread(list_image[0]).shape[1]
heighth = cv2.imread(list_image[0]).shape[0]
video_out = cv2.VideoWriter(video_path, fourcc, fsp, (width,heighth))

for i in list_image:
    print(i)
    frame = cv2.imread(i)
    video_out.write(frame)

video_out.release()


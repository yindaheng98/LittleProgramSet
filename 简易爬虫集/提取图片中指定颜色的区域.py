#!/usr/bin/env python
# -*-coding:utf-8-*-
import cv2
import os
import re

root = os.path.split(__file__)[0]
img_dir = os.path.join(root, "selected")

src_imname_re = re.compile(r'.*[^z].jpg$')  # 哪些文件是被减数
src_imkey_re = re.compile(r'(.*?).jpg$')  # 如何从被减数文件名中提取文件标识以与减数文件匹配
sub_imname_re = re.compile(r'.*z.jpg$')  # 哪些文件是减数
sub_imkey_re = re.compile(r'(.*?)z.jpg')  # 如何从减数文件名中提取文件标识以与被减数文件匹配


def dst_impath_fmt(key):
    p = os.path.join(root, "result")
    return os.path.join(p, key+".jpg")


list_image = os.listdir(img_dir)
dict_image = {}
for impath in list_image:
    print(impath)
    if src_imname_re.match(impath) != None:
        k = re.findall(src_imkey_re, impath)[0]
        if k in dict_image:
            dict_image[k][0] = impath
        else:
            dict_image[k] = [impath, None]
    elif sub_imname_re.match(impath) != None:
        k = re.findall(sub_imkey_re, impath)[0]
        if k in dict_image:
            dict_image[k][1] = impath
        else:
            dict_image[k] = [None, impath]
print(dict_image)

alpha = 0.5
for k, v in dict_image.items():
    src = os.path.join(img_dir, v[0])
    sub = os.path.join(img_dir, v[1])
    dst = dst_impath_fmt(k)
    src_img = cv2.imread(src)
    sub_img = cv2.imread(sub)
    src_img = cv2.cvtColor(src_img, cv2.COLOR_RGB2GRAY)
    sub_img = cv2.cvtColor(sub_img, cv2.COLOR_RGB2GRAY)
    dst_img = src_img-sub_img
    _, dst_img = cv2.threshold(dst_img, 127, 255, cv2.THRESH_BINARY)
    dst_img=cv2.medianBlur(dst_img,5)
    cv2.imwrite(dst, dst_img)
    print(src, "-", sub, "=", dst)

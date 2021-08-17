#!/usr/bin/env python
# -*-coding:utf-8-*-
import cv2
import os
import re
import numpy as np

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
    if None in v:
        continue
    src = os.path.join(img_dir, v[0])
    sub = os.path.join(img_dir, v[1])
    dst = dst_impath_fmt(k)
    src_img = cv2.imread(src)
    sub_img = cv2.imread(sub)
    diff = cv2.absdiff(src_img,sub_img) #先求差
    mask = cv2.cvtColor(diff, cv2.COLOR_RGB2GRAY) #转灰度
    _, mask = cv2.threshold(mask, 0, 255, cv2.THRESH_OTSU) #自适应阈值化为掩膜
    mask = cv2.dilate(mask,cv2.getStructuringElement(cv2.MORPH_RECT,(3,3)),iterations=3) #把掩膜进行形态学膨胀三次
    mask = cv2.morphologyEx(mask,cv2.MORPH_CLOSE,cv2.getStructuringElement(cv2.MORPH_RECT,(3,3)),iterations=3) #再把掩膜进行形态学闭运算三次
    dst_img=cv2.add(sub_img, np.zeros(np.shape(sub_img), dtype=np.uint8), mask=mask) #用处理好的掩膜提取原图像中的文字区域
    # 至此，文字区域提取完成
    dst_img = cv2.cvtColor(dst_img, cv2.COLOR_RGB2GRAY) #文字区域转灰度
    _, dst_img = cv2.threshold(dst_img, 128+64, 255, cv2.THRESH_BINARY) #文字区域阈值化
    cv2.imwrite(dst, dst_img) #搞定
    print(src, "-", sub, "=", dst)

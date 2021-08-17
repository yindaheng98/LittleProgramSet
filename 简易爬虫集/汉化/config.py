#!/usr/bin/env python
# -*-coding:utf-8-*-
import os
import re

root = os.path.split(__file__)[0]
img_dir = os.path.join(root, "selected")

src_imname_re = re.compile(r'.*[^z].jpg$')
src_imkey_re = re.compile(r'(.*?).jpg$')
sub_imname_re = re.compile(r'.*z.jpg$')
sub_imkey_re = re.compile(r'(.*?)z.jpg')

im_res = [
    {
        'src': {
            'name': re.compile(r'.*[^z].jpg$'),  # 哪些文件是被减数
            'key': re.compile(r'(.*?).jpg$'),  # 如何从被减数文件名中提取文件标识以与减数文件匹配
        },
        'sub': {
            'name': re.compile(r'.*z.jpg$'),  # 哪些文件是减数
            'key': re.compile(r'(.*?)z.jpg$'),  # 如何从减数文件名中提取文件标识以与被减数文件匹配
        },
    },
    {
        'src': {
            'name': re.compile(r'[0-9]+_.*[^z].jpg$'),  # 哪些文件是被减数
            # 如何从被减数文件名中提取文件标识以与减数文件匹配
            'key': re.compile(r'[0-9]+_(.*?).jpg$'),
        },
        'sub': {
            'name': re.compile(r'[0-9]+_.*z.jpg$'),  # 哪些文件是减数
            # 如何从减数文件名中提取文件标识以与被减数文件匹配
            'key': re.compile(r'[0-9]+_(.*?)z.jpg$'),
        },
    },
]


def dst_impath_fmt(key):
    p = os.path.join(root, "result")
    return os.path.join(p, key+".jpg")


list_image = os.listdir(img_dir)
dict_image = {}
for impath in list_image:
    for im_re in im_res:
        src_imname_re = im_re['src']['name']
        src_imkey_re = im_re['src']['key']
        sub_imname_re = im_re['sub']['name']
        sub_imkey_re = im_re['sub']['key']
        if src_imname_re.match(impath) != None:
            k = re.findall(src_imkey_re, impath)[0]
            if k in dict_image:
                dict_image[k][0] = os.path.join(img_dir, impath)
            else:
                dict_image[k] = [os.path.join(img_dir, impath), None]
            print(impath, '->', k, '->', dict_image[k])
        elif sub_imname_re.match(impath) != None:
            k = re.findall(sub_imkey_re, impath)[0]
            if k in dict_image:
                dict_image[k][1] = os.path.join(img_dir, impath)
            else:
                dict_image[k] = [None, os.path.join(img_dir, impath)]
            print(impath, '->', k, '->', dict_image[k])
        else:
            print(impath)
_dict_image = {}
for k, v in dict_image.items():
    if None in v:
        continue
    _dict_image[k] = v
dict_image = _dict_image
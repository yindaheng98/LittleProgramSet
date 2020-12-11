import os
import re

root = os.path.split(__file__)[0]

list_image = os.listdir(root)

for ori in list_image:
    new = re.sub(r'^[0-9]+_', "", ori)
    if ori == new:
        continue
    src = os.path.join(root, ori)
    dst = os.path.join(root, new)
    print(src, "->", dst)
    if os.path.exists(dst):
        print(dst, "已存在")
        continue
    os.rename(src, dst)

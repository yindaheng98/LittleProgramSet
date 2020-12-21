import os
import re

def process_dir(root):
    list_image = os.listdir(root)
    for ori in list_image:
        src = os.path.join(root, ori)
        if os.path.isdir(src):
            process_dir(src)
            continue
        new = re.sub(r'^[0-9]+_', "", ori)
        if ori == new:
            continue
        dst = os.path.join(root, new)
        print(src, "->", dst)
        if os.path.exists(dst):
            print(dst, "已存在")
            continue
        os.rename(src, dst)

if __name__ == "__main__":
    process_dir(os.path.split(__file__)[0])
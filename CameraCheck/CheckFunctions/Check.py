from CheckFunctions.zhedang import zhedang
from CheckFunctions.zaodian import zaodian
from CheckFunctions.zhuandong import zhuandong
from CheckFunctions.sepian import sepian
from CheckFunctions.mohu import mohu
from CheckFunctions.huangdong import huangdong



def Check(frame):
    return {
        "遮挡": zhedang(frame),
        "转动": zhuandong(frame),
        "晃动": huangdong(frame),
        "色偏": sepian(frame),
        "模糊": mohu(frame),
        "噪点": zaodian(frame)}

import pathlib

N = 300
data_dir = '图片和数据'
pathlib.Path('.', data_dir).mkdir(parents=True, exist_ok=True)
data_path = pathlib.Path('.', data_dir, '顾客数量=%d.数据.json' % N)

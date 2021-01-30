'''
将坚果云Webdav中的文件（不包含子目录）备份到Aliyun OSS的指定Bucket
'''
import logging
from webdav3.client import Client
import oss2
from datetime import datetime
import json
import optparse
import os
import time
dtf = "%Y-%m-%d %H:%M:%S"
now_str = datetime.now().strftime(dtf)
logger = logging.getLogger()
logger.setLevel(logging.INFO)
ch = logging.StreamHandler()
ch.setLevel(logging.INFO)
formatter = logging.Formatter(
    '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
ch.setFormatter(formatter)
logger.addHandler(ch)

def print(s):
    logger.info(s)

def copy_file(finfo, temp_dir, client, bucket):
    fname = finfo['name']
    local_path = temp_dir+"/"+fname
    print("正在下载%s到%s" % (fname, local_path))
    client.download_sync(fname, local_path)
    print("已经下载%s到%s" % (fname, local_path))
    print("正在上传%s到Aliyun" % local_path)
    bucket.put_object_from_file(fname, local_path)
    print("已经上传%s到Aliyun" % local_path)
    os.remove(local_path)


def main():
    parser = optparse.OptionParser()
    parser.add_option('-w', '--webdav-client-options', dest='client_options',
                      type='string', help='连接webdav服务器的JSON格式设置，见https://github.com/ezhov-evgeny/webdav-client-python-3', default='{'+'}')

    parser.add_option('-i', '--AccessKeyId', dest='AccessKeyId', type='string',
                      help='AccessKeyId for accessing Aliyun OSS')
    parser.add_option('-k', '--AccessKeySecret', dest='AccessKeySecret', type='string',
                      help='AccessKeySecret for accessing Aliyun OSS')
    parser.add_option('-e', '--Endpint', dest='Endpint', type='string',
                      help='Copy to which Endpint in Aliyun OSS', default='http://oss-cn-hangzhou.aliyuncs.com')
    parser.add_option('-b', '--Bucket', dest='Bucket', type='string',
                      help='Copy to which Bucket in Aliyun OSS', default='zotero-backup')

    parser.add_option('-a', '--all', dest='all',
                      action="store_true", help='是否复制全部文件', default=False)
    parser.add_option('-s', '--since', dest='since', type='string',
                      help='复制修改时间在此之后的文件，格式为"'+dtf+'", 例如 '+now_str,
                      default=now_str)
    parser.add_option('-u', '--until', dest='until', type='string',
                      help='复制修改时间在此之前的文件，格式为"'+dtf+'", 例如 '+now_str,
                      default=now_str)
    parser.add_option('-f', '--datetime-format', dest='dtf', type='string',
                      help='Webdav系统中获取到的时间格式',
                      default="%a, %d %b %Y %H:%M:%S GMT")
    parser.add_option('-t', '--temp-dir', dest='temp_dir', type='string',
                      help='临时目录路径',
                      default=os.getcwd())
    parser.add_option('-d', '--delay', dest='delay', type='int',
                      help='下载文件的时间间隔（防被封）',
                      default=0)
    options, _ = parser.parse_args()
    print("正在连接Webdav")
    client = Client(json.loads(options.client_options))
    finfolist = client.list(get_info=True)
    print("Webdav已连接")
    print("正在连接Aliyun OSS")
    auth = oss2.Auth(options.AccessKeyId, options.AccessKeySecret)
    bucket = oss2.Bucket(auth, options.Endpint, options.Bucket)
    bucket.create_bucket(oss2.models.BUCKET_ACL_PRIVATE)
    print("Aliyun OSS已连接")

    if options.all:
        print("复制所有文件")
    else:
        print("复制从%s到%s的所有文件" % (options.since, options.until))
    for finfo in finfolist:
        if finfo['isdir']:
            continue
        if options.all:
            copy_file(finfo, options.temp_dir, client, bucket)
        else:
            modified = datetime.strptime(finfo['modified'], options.dtf)
            since = datetime.strptime(options.since, dtf)
            until = datetime.strptime(options.until, dtf)
            if modified >= since and modified <= until:
                copy_file(finfo, options.temp_dir, client, bucket)
        time.sleep(options.delay)


main()

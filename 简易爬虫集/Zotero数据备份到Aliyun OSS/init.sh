#!/bin/bash
apt-get install -y unzip
ROOT=$(pwd)
TEMP_ZIP=$ROOT/rclone.zip
wget --no-check-certificate https://downloads.rclone.org/v1.54.1/rclone-v1.54.1-linux-amd64.zip -O $TEMP_ZIP
unzip -jo -d $ROOT $TEMP_ZIP
CONF=$ROOT/rclone.conf
cat > $CONF << EOF
[oss]
type = s3
provider = Alibaba
env_auth = false
access_key_id = ${akID}
secret_access_key = ${akScrt}
endpoint = oss-cn-hangzhou.aliyuncs.com
acl = private
storage_class = STANDARD

[onedrive]
type = onedrive
client_id = ${client_id}
client_secret = ${client_secret}
region = global
token = ${token}
drive_id = 40f47af77092ccff
drive_type = personal

[jianguoyun]
type = webdav
url = https://dav.jianguoyun.com/dav/
vendor = other
user = ${username}
pass = ${password}
EOF
chmod a+x $ROOT/rclone
EXEC="$ROOT/rclone --config $CONF --log-level INFO"

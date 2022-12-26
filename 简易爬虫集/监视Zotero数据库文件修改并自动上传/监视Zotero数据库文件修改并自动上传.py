import os
import sys
from datetime import datetime
from webdav4.client import Client
from config import config

PathToScript = os.path.dirname(sys.argv[0])
PathToSqlite = os.path.join(PathToScript, "zotero.sqlite")
PathToRecord = os.path.join(PathToScript, "zotero.sqlite.LastWriteTime.txt")
RecordLastWriteTime = os.path.getmtime(PathToRecord) if os.path.exists(PathToRecord) else 0
LastWriteTime = os.path.getmtime(PathToSqlite)
if RecordLastWriteTime == LastWriteTime:
    print(RecordLastWriteTime, "==", LastWriteTime)
    exit(0)
client = Client(**config)
client.upload_file(PathToSqlite, "zotero/zotero.sqlite", overwrite=True)
with open(PathToRecord, "w", encoding='utf8') as f:
    f.write(str(datetime.fromtimestamp(LastWriteTime)))
os.utime(PathToRecord, (LastWriteTime, LastWriteTime))

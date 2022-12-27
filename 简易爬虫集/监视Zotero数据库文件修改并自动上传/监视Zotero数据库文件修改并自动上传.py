import os
import sys
from datetime import datetime
from webdav4.client import Client
from config import config

PathToScript = os.path.dirname(sys.argv[0])
PathToSqlite = os.path.join(PathToScript, "zotero.sqlite")
PathToRecord = os.path.join(PathToScript, "zotero.sqlite.LastSize.txt")


try:
    with open(PathToRecord, "r", encoding='utf8') as f:
        RecordSize = int(f.read())
except Exception as e:
    print(e)
    RecordSize = 0
Size = os.path.getsize(PathToSqlite)
if RecordSize == Size:
    print(RecordSize, "==", Size)
    exit(0)
print(RecordSize, "!=", Size)

RecordLastWriteTime = os.path.getmtime(PathToRecord) if os.path.exists(PathToRecord) else 0
LastWriteTime = os.path.getmtime(PathToSqlite)
if RecordLastWriteTime == LastWriteTime:
    print(RecordLastWriteTime, "==", LastWriteTime)
    exit(0)
print(RecordLastWriteTime, "!=", LastWriteTime)

client = Client(**config, timeout=300, trust_env=False)
client.upload_file(PathToSqlite, "zotero/zotero.sqlite", overwrite=True)

print("RecordSize", Size)
with open(PathToRecord, "w", encoding='utf8') as f:
    f.write(str(Size))

print("LastWriteTime", LastWriteTime)
os.utime(PathToRecord, (LastWriteTime, LastWriteTime))

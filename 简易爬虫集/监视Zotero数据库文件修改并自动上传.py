import os
import sys
from datetime import datetime
import subprocess

PathToScript = os.path.dirname(sys.argv[0])
PathToSqlite = os.path.join(PathToScript, "zotero.sqlite")
PathToRecord = os.path.join(PathToScript, "zotero.sqlite.LastWriteTime.txt")
RecordLastWriteTime = os.path.getmtime(PathToRecord) if os.path.exists(PathToRecord) else 0
LastWriteTime = os.path.getmtime(PathToSqlite)
if RecordLastWriteTime == LastWriteTime:
    exit(0)
subprocess.run([
    os.path.join(PathToScript, "rclone.exe"),
    "--log-level", "DEBUG",
    "copy",
    PathToSqlite,
    "jianguoyun:zotero"
])
with open(PathToRecord, "w", encoding='utf8') as f:
    f.write(str(datetime.fromtimestamp(LastWriteTime)))
os.utime(PathToRecord, (LastWriteTime, LastWriteTime))

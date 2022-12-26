$PathToScript = (Split-Path -Parent $MyInvocation.MyCommand.Definition)
$PathToSqlite = "$PathToScript\zotero.sqlite"
$PathToRecord = "$PathToScript\zotero.sqlite.LastWriteTime.txt"
$RecordLastWriteTime = (Get-ChildItem $PathToRecord).LastWriteTime
$LastWriteTime = (Get-ChildItem $PathToSqlite).LastWriteTime
if ($RecordLastWriteTime -eq $LastWriteTime) {
    exit 0
}
& "D:\Documents\MyPrograms\rclone-v1.61.1-windows-amd64\rclone.exe" --log-level DEBUG copy $PathToSqlite jianguoyun:zotero
Write-Output $LastWriteTime > $PathToRecord
(Get-ChildItem $PathToRecord).LastWriteTime = $LastWriteTime
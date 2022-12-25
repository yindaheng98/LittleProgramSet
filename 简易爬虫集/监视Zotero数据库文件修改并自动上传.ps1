$PathToMonitor = "D:\Documents\Zotero\zotero.sqlite"
$PathToRecord = "D:\Documents\Zotero\zotero.sqlite.LastWriteTime.txt"
$RecordLastWriteTime = (Get-Content $PathToRecord)
$LastWriteTime = (Get-ChildItem $PathToMonitor).LastWriteTime
if ($RecordLastWriteTime -eq $LastWriteTime) {
    exit 0
}

(Write-Output $LastWriteTime) > $PathToRecord
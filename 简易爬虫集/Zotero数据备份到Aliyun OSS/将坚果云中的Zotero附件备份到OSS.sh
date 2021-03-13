#!/bin/bash
source $(dirname ${BASH_SOURCE[0]})/init.sh
$EXEC ls jianguoyun:zotero
$EXEC copy jianguoyun:zotero oss:zotero-backup/attachments

#!/bin/bash
source $(dirname ${BASH_SOURCE[0]})/init.sh
$EXEC ls --exclude 'storage/**' onedrive:zotero
$EXEC copy --exclude 'storage/**' onedrive:zotero oss:zotero-backup/database

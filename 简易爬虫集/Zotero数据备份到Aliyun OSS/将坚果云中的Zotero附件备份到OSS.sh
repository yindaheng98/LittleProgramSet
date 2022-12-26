#!/bin/bash -x
source $(dirname ${BASH_SOURCE[0]})/init.sh
$EXEC copy jianguoyun:zotero/zotero.sqlite ./
for i in $(echo "select key from items;" | $SQLT ./zotero.sqlite); do
    $EXEC ls jianguoyun:zotero/$i.zip
    if [$? -eq 0]; then
        $EXEC copy jianguoyun:zotero/$i.zip oss:zotero-backup/attachments
    fi
    $EXEC ls jianguoyun:zotero/$i.prop
    if [$? -eq 0]; then
        $EXEC copy jianguoyun:zotero/$i.prop oss:zotero-backup/attachments
    fi
done

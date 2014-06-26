#!/bin/bash
PASTA=simulator
tar -zcvf /tmp/backup_$PASTA.tar.gz ~/c/$PASTA/
echo "`date`" | mutt -a /tmp/backup_$PASTA.tar.gz -s "backup da pasta $PASTA" dmelo87@gmail.com
rm /tmp/backup_$PASTA.tar.gz

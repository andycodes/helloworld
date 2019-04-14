#!/bin/sh

OBJ_DIR=/project/tmp

FILE_TGZ=$(ls |grep tgz)
LOCAL=/usr/local
echo $FILE_TGZ
rm $OBJ_DIR -rf
mkdir $OBJ_DIR -p
tar zxvf $FILE_TGZ -C $OBJ_DIR
cp  $OBJ_DIR/opt/FriendlyARM/toolschain/4.5.1/  $LOCAL  -rf
echo "export PATH=${LOCAL}/4.5.1/bin:$PATH">>/etc/bash.bashrc

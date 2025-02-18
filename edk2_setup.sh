#!/bin/bash

SRC_DIR="/workspaces/mikanos"
EDK2_DIR="$HOME/edk2"
EDK2_ARM_DIR="$SRC_DIR/edk2"

# edk2のセットアップ
source $EDK2_DIR/edksetup.sh

# edk2のビルド時のターゲット設定を上書きする
cp $EDK2_ARM_DIR/Conf/target.txt $EDK2_DIR/Conf/target.txt

# edk2の設定をApple Silicon用に上書きする
cp $EDK2_ARM_DIR/Conf/tools_def.txt $EDK2_DIR/Conf/tools_def.txt

# 既に存在するedk2/MikanLoaderPkgのリンク削除する
if [ -e "$EDK2_DIR/MikanLoaderPkg" ]; then
    unlink $EDK2_DIR/MikanLoaderPkg
fi

# ブートローダーのディレクトリをedk2側にリンクしてビルドできるようにする
ln -s $SRC_DIR/$1/MikanLoaderPkg $EDK2_DIR
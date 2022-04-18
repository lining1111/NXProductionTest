#!/bin/bash

echo "你好"
##进入脚本所在路径
basedir=`cd $(dirname $0); pwd -P`
cd $basedir

echo "1">log

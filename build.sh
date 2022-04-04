#!/bin/bash

clear="$*" #获取环境变量

clear()
{
    rm -rf CMakeFiles
    rm *cmake*
    rm CMakeCache.txt
    rm Makefile
}

build()
{
    cmake .
    make
}

if [ "${clear}" = "clear" ]
then
    clear
    cd test
    clear
    cd ..

else
    build
fi
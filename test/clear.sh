#!/bin/bash


find .  -not -name '*.cpp' -not -name 'clear.sh'  -not -name 'CMakeLists.txt'  -delete
rm -rf CMakeFiles
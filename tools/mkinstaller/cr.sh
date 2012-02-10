#!/bin/sh
NAME=GOLsetup
rm $NAME.* > /dev/null 2>&1
7zr a $NAME.7z dist/* -m0=BCJ2 -m1=LZMA:d25:fb255 -m2=LZMA:d19 -m3=LZMA:d19 -mb0:1 -mb0s1:2 -mb0s2:3 -mx
cat *.sfx $NAME.7z > $NAME.exe

#! /usr/bin/bash
cd /c/Users/Elève/desktop/document/progra/hpcp
echo $(gcc -shared -Os -s -o lib/libhpcp.dll src/hpcp.c -I ./include)
echo $(gcc -Os -s -L. ./main.c -L ./lib -lhpcp -o ./bin/main -I ./include)
./bin/main
read ok
#! /usr/bin/bash
cd /c/Users/Elève/desktop/document/progra/hpcp
echo $(gcc -shared -Os -s -o bin/libhpcp.dll src/hpcp.c -I ./include)
echo $(gcc -shared -Os -s -o lib/libhpcp.lib src/hpcp.c -I ./include)
echo $(gcc -Os -s ./main.c -L ./lib -lhpcp -o ./bin/main -I ./include)
./bin/main
echo "press any key to continue..."
read ok
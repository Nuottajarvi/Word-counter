#bin/bash

clear
g++ wordcounter.c linkedlist.c hashmap.c -o wordcounter.exe
./wordcounter.exe "test.txt"
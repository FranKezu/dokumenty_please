@echo off
gcc main.c src\extra.c src\hashmap.c src\heap.c src\list.c src\map.c -o bin\run.exe
bin\run.exe

pause
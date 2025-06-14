@echo off
gcc main.c src\extra.c src\hashmap.c src\list.c src\menu.c -o bin\run.exe
bin\run.exe

pause
@echo off
chcp 65001 > nul
gcc main.c src\extra.c src\hashmap.c src\list.c src\menu.c src\queue.c src\game.c -o bin\run.exe
bin\run.exe

pause
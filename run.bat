@ECHO OFF
set debug=-Wall -Wextra
set std=-std=gnu11
set include=-fopenmp
set op=-Ofast
set asm=gcc src\prime18.c %std% %include% %op% -fverbose-asm -S -o bin\prime18_op.S

gcc src\prime18.c %debug% %std% %include% %op% -o bin\prime18
bin\prime18.exe

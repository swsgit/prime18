@ECHO OFF
set debug=-Wall -Wextra -g
set std=-std=gnu11
set include=-fopenmp
set op=-Ofast
set asm=gcc prime18.c %std% %include% %op% -fverbose-asm -S -o prime18_op.S
%asm%
gcc prime18.c %debug% %std% %include% %op% -o prime18

@echo off

set EXE=filedez
set DEP_FILES="filedez.c dezcrypt.c"

echo Compilin that shiz
echo Running gcc -o %EXE% %DEP_FILES%
gcc -o %EXE% %DEP_FILES%

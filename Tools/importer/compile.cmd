@echo off
%~dp0..\tcc\tcc -I%~dp0..\..\Engine -o %~dp0importer.exe ^
    %~dp0image.c ^
    %~dp0main.c
if errorlevel 1 exit /B 1
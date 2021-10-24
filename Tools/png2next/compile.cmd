@echo off
%~dp0..\tcc\tcc -I%~dp0..\..\Engine -o %~dp0png2next.exe %~dp0png2next.c
if errorlevel 1 exit /B 1
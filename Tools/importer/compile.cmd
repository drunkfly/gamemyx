@echo off
%~dp0..\tcc\tcc -I%~dp0..\..\Engine -DEZXML_NOMMAP -o %~dp0importer.exe ^
    %~dp0ezxml/ezxml.c ^
    %~dp0md5/md5.c ^
    %~dp0image.c ^
    %~dp0tilecache.c ^
    %~dp0tilemap.c ^
    %~dp0tileset.c ^
    %~dp0main.c
if errorlevel 1 exit /B 1
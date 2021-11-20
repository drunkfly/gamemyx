@echo off
setlocal

set PATH=%~dp0Tools\z88dk\bin;%~dp0Tools\tcc;%PATH%
set ZCCCFG=%~dp0Tools\z88dk\lib\config

if not exist %~dp0Build\CMake.Next mkdir %~dp0Build\CMake.Next
if errorlevel 1 exit /B 1

cd %~dp0Build\CMake.Next
if errorlevel 1 exit /B 1

if exist %~dp0Build\CMake.Next\CMakeCache.txt goto cmake_exists
%~dp0Tools\cmake\bin\cmake ^
    -G "MinGW Makefiles" ^
    -DCMAKE_MAKE_PROGRAM=%~dp0Tools\make\mingw32-make ^
    -DCMAKE_TOOLCHAIN_FILE=%~dp0Build\z88dk.cmake ^
    -DTARGET_ZXNEXT=YES ^
    %~dp0Build
if errorlevel 1 exit /B 1
:cmake_exists

%~dp0Tools\make\mingw32-make -j 4
if errorlevel 1 exit /B 1

copy /y %~dp0Build\Sync\Build\GameMyx.nex Z:\
if errorlevel 1 exit /B 1

@echo off
setlocal

set PATH=%~dp0Tools\z88dk\bin;%PATH%
set ZCCCFG=%~dp0Tools\z88dk\lib\config

if not exist %~dp0Build\CMake mkdir %~dp0Build\CMake
if errorlevel 1 exit /B 1

cd %~dp0Build\CMake
if errorlevel 1 exit /B 1

%~dp0Tools\cmake\bin\cmake ^
    -G "MinGW Makefiles" ^
    -DCMAKE_MAKE_PROGRAM=%~dp0Tools\make\mingw32-make ^
    -DCMAKE_TOOLCHAIN_FILE=%~dp0Build\z88dk.cmake ^
    %~dp0Build
if errorlevel 1 exit /B 1

%~dp0Tools\make\mingw32-make
if errorlevel 1 exit /B 1

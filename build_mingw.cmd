@echo off
setlocal

set PATH=%~dp0Tools\tcc;%PATH%

if not exist %~dp0Build\CMake.MinGW mkdir %~dp0Build\CMake.MinGW
if errorlevel 1 exit /B 1

if not exist %~dp0Build\Importer mkdir %~dp0Build\Importer
if errorlevel 1 exit /B 1

if not exist %~dp0Build\MMapView mkdir %~dp0Build\MMapView
if errorlevel 1 exit /B 1

cd %~dp0Build\CMake.MinGW
if errorlevel 1 exit /B 1

if exist %~dp0Build\CMake.MinGW\CMakeCache.txt goto cmake_exists
%~dp0Tools\cmake\bin\cmake ^
    -G "MinGW Makefiles" ^
    -DTARGET_SDL2=YES ^
    %~dp0Build
if errorlevel 1 exit /B 1
:cmake_exists

%~dp0Tools\cmake\bin\cmake --build . --config Release
if errorlevel 1 exit /B 1

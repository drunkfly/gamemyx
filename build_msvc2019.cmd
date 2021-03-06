@echo off
setlocal

set PATH=%~dp0Tools\tcc;%PATH%

if not exist %~dp0Build\CMake.MSVC2019 mkdir %~dp0Build\CMake.MSVC2019
if errorlevel 1 exit /B 1

if not exist %~dp0Build\Importer mkdir %~dp0Build\Importer
if errorlevel 1 exit /B 1

if not exist %~dp0Build\MMapView mkdir %~dp0Build\MMapView
if errorlevel 1 exit /B 1

cd %~dp0Build\CMake.MSVC2019
if errorlevel 1 exit /B 1

if exist %~dp0Build\CMake.MSVC2019\CMakeCache.txt goto cmake_exists
%~dp0Tools\cmake\bin\cmake ^
    -G "Visual Studio 16 2019" ^
    -A Win32 ^
    -DTARGET_SDL2=YES ^
    %~dp0Build
if errorlevel 1 exit /B 1
:cmake_exists

%~dp0Tools\cmake\bin\cmake --build . --config Release
if errorlevel 1 exit /B 1

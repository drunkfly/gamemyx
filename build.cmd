@echo off
setlocal

set PATH=%~dp0Tools\z88dk\bin;%PATH%
set ZCCCFG=%~dp0Tools\z88dk\lib\config
rem set NAME=MyxDemo

Tools\make\mingw32-make

rem cd %~dp0
rem if errorlevel 1 exit /B 1

rem if not exist %~dp0Build\Sync\Build mkdir %~dp0Build\Sync\Build
rem if errorlevel 1 exit /B 1

rem zcc +zxn ^
rem     -IC:/Work2/NextGame/Engine ^
rem 	-clib=classic ^
rem     --opt-code-size ^
rem 	-lndos ^
rem 	-lesxdos ^
rem     -m ^
rem 	-create-app ^
rem 	-subtype=nex ^
rem     -o "C:/Work2/NextGame/Build/Bin/MyxDemo.nex" ^
rem 	test.c
rem if errorlevel 1 exit /B 1

rem zcc +zxn -IC:/Work2/NextGame/Engine -clib=classic
rem --opt-code-size  -lndos -lesxdos -m -create-app -subtype=nex -o "C:/Work2/NextGame/Build/Bin/MyxDemo.nex" test.c

rem copy /b %~dp0Build\%NAME%.nex %~dp0Build\Sync\Build\%NAME%.nex
rem if errorlevel 1 exit /B 1

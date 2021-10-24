@echo off
setlocal

set PATH=%~dp0Tools\z88dk\bin;%PATH%
set ZCCCFG=%~dp0Tools\z88dk\lib\config
set NAME=game

cd %~dp0
if errorlevel 1 exit /B 1

if not exist %~dp0Build\Sync\Build mkdir %~dp0Build\Sync\Build
if errorlevel 1 exit /B 1

zcc +zxn ^
    -I%~dp0Engine ^
	-clib=classic ^
	-lndos ^
	-lesxdos ^
    -m ^
	--opt-code-size ^
	-o %~dp0Build\%NAME% ^
	-create-app ^
	-subtype=nex ^
	test.c
if errorlevel 1 exit /B 1

copy /b %~dp0Build\%NAME%.nex %~dp0Build\Sync\Build\%NAME%.nex
if errorlevel 1 exit /B 1

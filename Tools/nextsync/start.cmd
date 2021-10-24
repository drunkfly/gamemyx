@echo off

if not exist %~dp0..\..\Build\Sync\Build mkdir %~dp0..\..\Build\Sync\Build
if errorlevel 1 exit /B 1

cd %~dp0..\..\Build\Sync
if errorlevel 1 exit /B 1

start python %~dp0server\nextsync.py
if errorlevel 1 exit /B 1

@echo off
rem Clean build and test artifacts.
rem Run from the test directory.

echo Cleaning build artifacts...

if exist test.exe del test.exe
if exist test.obj del test.obj
if exist ini.obj  del ini.obj
if exist output.ini  del output.ini
if exist scratch.ini del scratch.ini

echo Done.

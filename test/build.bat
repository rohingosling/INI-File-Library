@echo off
rem Build the INI library test program.
rem Run from the test directory.

echo Building test.exe...
bcc -ml -I.. test.cpp ..\ini.cpp > build.log

if errorlevel 1 goto failed

echo Build succeeded.
goto end

:failed
echo Build failed. See build.log for details.

:end

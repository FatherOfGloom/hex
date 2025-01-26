@echo off
call ./build.bat
echo: 
if %errorlevel% neq 0 exit /b %errorlevel%
pushd .\bin\
@REM start ./hex.exe
hex.exe
popd
set CFLAGS=-lgdi32 -lwinmm -lgmp
set UCPATH=lib\unholyc\src
set SRCFILES=..\src\main.c 

@REM mkdir include
xcopy /b /v /y %UCPATH%\unholy.c %INCLUDE%
xcopy /b /v /y %UCPATH%\unholy.h %INCLUDE%
if %errorlevel% neq 0 exit /b %errorlevel%

mkdir bin
pushd bin
gcc -o hex.exe -I%INCLUDE% %SRCFILES% %INCLUDE%\unholy.c %CFLAGS%
if %errorlevel% neq 0 exit /b %errorlevel%
echo build success
popd
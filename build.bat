set CFLAGS=-lgdi32 -lwinmm -lgmp
set SRC=main.c hex.c vec.c str.c

setlocal enabledelayedexpansion

if not exist bin mkdir bin

set SRC_FILES=

for %%i in (%SRC%) do (
    set SRC_FILES=!SRC_FILES! ..\src\%%i
)

set SRC_FILES=%SRC_FILES:~1%

pushd bin

gcc -o hex.exe %SRC_FILES% %CFLAGS%

if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

echo build success
popd

endlocal
@echo off
setlocal enabledelayedexpansion

REM Define paths
set SRC_DIR=%CD%\src
set BIN_DIR=%CD%\bin
set LIB_DIR=%CD%\lib

REM Create output directory if it doesn't exist
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"
if not exist "%LIB_DIR%" mkdir "%LIB_DIR%"

REM Loop through all .cpp files in the src directory
for %%f in (%SRC_DIR%\*.cpp) do (
    REM Extract the filename without extension
    set "filename=%%~nf"
    echo FN !filename! %%f
    
    REM Compile the .cpp file into a .dll
    cl.exe /LD /EHsc /std:c++20 /I%CD%\include %%f /link /OUT:%BIN_DIR%\!filename!.dll
)

endlocal

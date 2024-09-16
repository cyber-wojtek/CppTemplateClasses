@echo off
setlocal enabledelayedexpansion

REM Define paths
set SRC_DIR=%CD%\src
set OUT_DIR=%CD%\bin

REM Create output directory if it doesn't exist
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

REM Loop through all .cpp files in the src directory
for %%f in (%SRC_DIR%\*.cpp) do (
    REM Extract the filename without extension
    set "filename=%%~nf"
    echo FN !filename! %%f
    
    REM Compile the .cpp file into a .dll
    cl.exe /LD /EHsc /std:c++latest /I%CD%\include %%f /link /OUT:%OUT_DIR%\!filename!.dll
)

endlocal

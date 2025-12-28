@echo off
setlocal enabledelayedexpansion

set PROJECT_ROOT=%cd%
set SRC_DIR=%PROJECT_ROOT%\src

cls

echo gathering files
set FILES=
    for /r "%SRC_DIR%" %%f in (*.cpp) do (
        set "FILES=!FILES! "%%f""
    )

echo running build
g++ -std=c++17 %FILES%  -I"%SRC_DIR%" -o "app.exe"

if %errorlevel% equ 0 (
    echo ======
    app.exe
) else (
    echo.
    echo epic build fail
)
 
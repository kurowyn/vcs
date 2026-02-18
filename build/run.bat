@set BIN=..\bin\vcs.exe
@set SRC=..\src\data\building.cpp ..\src\data\random.cpp ..\src\gui\asset.cpp ..\src\gui\gui.cpp ..\src\gui\box.cpp ..\src\gui\main.cpp
@set FLAGS=-g -std=c++23 -Wunused
@set LIBS=-I include -L lib -lraylib -lgdi32 -lwinmm -lstdc++exp
@set CC=g++.exe

%CC% %FLAGS% -o %BIN% %SRC% %LIBS% 
@if %errorlevel% neq 0 (
    @echo Compilation failed!
    @exit /b
)
%BIN%

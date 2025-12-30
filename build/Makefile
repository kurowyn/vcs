BIN=../bin/vcs.exe
SRC=../src/data/building.cpp ../src/data/random.cpp ../src/gui/asset.cpp ../src/gui/gui.cpp  \
	../src/gui/box.cpp ../src/gui/main.cpp
FLAGS=-g -std=c++23 -Wunused
LIBS=-I include -L lib -lraylib -lgdi32 -lwinmm -lstdc++exp
CC=/mnt/c/w64devkit/bin/g++.exe
LINUX_BIN=../bin/vcs
LINUX_LIBS=-lraylib
LINUX_CC=g++

build: $(SRC)
	$(CC) $(FLAGS) -o $(BIN) $(SRC) $(LIBS)
run: 
	./$(BIN)


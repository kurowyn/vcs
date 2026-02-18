BIN=../bin/vcs.exe
SRC=../src/data/building.cpp ../src/data/random.cpp ../src/gui/asset.cpp ../src/gui/gui.cpp  \
	../src/gui/box.cpp ../src/gui/main.cpp
FLAGS=-g -std=c++23 -Wunused
LIBS=-I include -L lib -lraylib -lgdi32 -lwinmm -lstdc++exp
CC=g++.exe

build: $(SRC)
	$(CC) $(FLAGS) -o $(BIN) $(SRC) $(LIBS)
run: 
	./$(BIN)


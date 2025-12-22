BIN=../bin/vcs.exe
SRC=../src/gui.cpp
FLAGS=-g -std=c++23 -Wunused
LIBS=-I include -L lib -lraylib -lgdi32 -lwinmm -lstdc++exp
CC=/mnt/c/w64devkit/bin/g++.exe 
build: $(SRC)
	$(CC) $(FLAGS) -o $(BIN) $(SRC) $(LIBS)
	sudo chown kurohen:kurohen $(BIN)
	chmod +x $(BIN)
run: 
	./$(BIN)


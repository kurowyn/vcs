BIN=../bin/vcs.exe
SRC= ../src/data/building.cpp ../src/gui/gui.cpp ../src/gui/box.cpp ../src/gui/main.cpp
#SRC= ../src/gui/menu.cpp ../src/gui/box.cpp
FLAGS=-g -std=c++23 -Wunused
LIBS=-I include -L lib -lraylib -lgdi32 -lwinmm -lstdc++exp
CC=/mnt/c/w64devkit/bin/g++.exe 
LINUX_BIN=../bin/vcs
LINUX_LIBS=-lraylib
LINUX_CC=g++

build: $(SRC)
	$(CC) $(FLAGS) -o $(BIN) $(SRC) $(LIBS)
	sudo chown kurohen:kurohen $(BIN)
	chmod +x $(BIN)
build_linux: $(SRC)
	$(LINUX_CC) $(FLAGS) -o $(LINUX_BIN) $(SRC) $(LINUX_LIBS)
	sudo chown kurohen:kurohen $(LINUX_BIN)
	chmod +x $(LINUX_BIN)
run: 
	./$(BIN)


BIN=./bin/vcs
SRC=./src/main.cpp
FLAGS=-g -std=c++23
CC=g++
build: main.cpp
	$(CC) $(FLAGS) -o $(BIN) $(SRC) 


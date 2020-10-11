CC=gcc
CFLAGS=-std=c99 -Wall -Wextra
EXE=ip_main

all: build

build: ip_main.c
	$(CC) $^ $(CFLAGS) -o $(EXE)

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(EXE)

.PHONY: clean run

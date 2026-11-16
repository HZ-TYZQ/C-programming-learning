CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

.PHONY: all test clean run

all: builds/test_zuma builds/zuma

test: builds/test_zuma
	./builds/test_zuma

run: builds/zuma
	./builds/zuma

clean:
	rm -rf builds/

builds/test_zuma: builds/test.o builds/zuma.o
	$(CC) $(CFLAGS) -o $@ $^

builds/zuma: builds/main.o builds/input.o builds/zuma.o
	$(CC) $(CFLAGS) -o $@ $^

builds/test.o: src/test.c src/zuma.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

builds/zuma.o: src/zuma.c src/zuma.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

builds/input.o: src/input.c src/input.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

builds/main.o: src/main.c src/zuma.h src/input.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

.PHONY: all test clean run

all: builds/ldm builds/test_ldm

# Compile device.c
builds/device.o: src/device.c src/device.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test.c
builds/test.o: src/test.c src/device.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Compile main.c
builds/main.o: src/main.c src/device.h src/input.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Compile input.c
builds/input.o: src/input.c src/input.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files(test)
builds/test_ldm: builds/test.o builds/device.o
	$(CC) $(CFLAGS) -o $@ $^

#Link object files(build)
builds/ldm: builds/main.o builds/device.o builds/input.o
	$(CC) $(CFLAGS) -o $@ $^

# Run tests
test: builds/test_ldm
	./builds/test_ldm

# Run build
run: builds/ldm
	./builds/ldm

# Remove build artifacts
clean:
	rm -f builds/*.o builds/test_ldm builds/ldm

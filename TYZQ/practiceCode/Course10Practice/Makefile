CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

TARGET = builds/test_ldm
OBJECTS = builds/device.o builds/test.o

.PHONY: all test clean

all: $(TARGET)

# Compile device.c
builds/device.o: src/device.c src/device.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Compile test.c
builds/test.o: src/test.c src/device.h
	mkdir -p builds
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Run tests
test: $(TARGET)
	./$(TARGET)

# Remove build artifacts
clean:
	rm -f $(TARGET) $(OBJECTS)

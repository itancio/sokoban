CC=g++
CFLAGS=-std=c++17 -ggdb -Wall -Werror -O2 -pedantic
TARGET=test_suite

$(TARGET): *.cpp ../../src/*.cpp
	$(CC) $(CFLAGS) *.cpp ../../src/*.cpp -o $(TARGET)

.PHONY: clean test

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

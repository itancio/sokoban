CC=g++
CFLAGS=-std=c++17 -ggdb3 -Wall -Werror -O2 -pedantic
TARGET=test_suite

$(TARGET): *.cpp ../../src/engine/sokoban.cpp
	$(CC) $(CFLAGS) *.cpp ../../src/engine/sokoban.cpp -o $(TARGET)

.PHONY: clean test

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

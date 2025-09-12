GXX = g++

COMPILEFLAGS = -g -Wall -Wextra -pedantic

SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

TARGET = tourists

#Default rule
all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

#Objects
%.o: %.c
	$(CXX) $(COMPILEFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
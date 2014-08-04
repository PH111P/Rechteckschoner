CC=g++
LDFLAGS=-lpng
CPPFLAGS=-c -std=c++11 -Os -Wall
SOURCES=main.cpp rectangle.cpp bitmap.cpp optparse.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=rechteckschoner

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -rf *o rechteckschoner
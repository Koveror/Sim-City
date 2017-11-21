EXECUTABLE=sim-city
CC=g++
SOURCES=main.cpp
OBJECTS=main.o
CPPFLAGS=-c -g -std=c++0x -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

$(OBJECTS): $(SOURCES)
	$(CC) $(CPPFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 

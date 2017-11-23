EXECUTABLE=sim-city
CC=g++
SOURCES=main.cpp graph.cpp vehicle.cpp
OBJECTS=main.o graph.o vehicle.o
CPPFLAGS=-c -g -std=c++11 -Wall -Wextra -pedantic
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

$(OBJECTS): $(SOURCES)
	$(CC) $(CPPFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 

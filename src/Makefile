EXECUTABLE=sim-city
CC=g++
SOURCES=main.cpp graph.cpp vehicle.cpp vertex.cpp edge.cpp
OBJECTS=main.o graph.o vehicle.o vertex.o edge.o
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

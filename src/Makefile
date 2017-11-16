EXECUTABLE=sim-city
CC=g++
SOURCES=main.cpp
OBJECTS=main.o
CPPFLAGS=-c
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system

$(OBJECTS): $(SOURCES)
	$(CC) $(CPPFLAGS) $(SOURCES)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) 

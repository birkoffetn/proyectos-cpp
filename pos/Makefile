CXXFLAGS= -Wall -ggdb
CC= g++

SOURCES= $(wildcard *.cpp)
OBJECTS= $(patsubst %.cpp,%.o,$(SOURCES))
BIN= ventas
DATA= ./data

all: $(BIN)
	@echo $(OBJECTS) $(DATA)
run: $(BIN)
	./$<

ventas: $(OBJECTS)
	$(CC) $^ -o $@
clean:
	$(RM) $(OBJECTS) $(BIN)
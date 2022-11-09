CXXFLAGS= -Wall -ggdb
SOURCES= $(wildcard *.cpp)
OBJECTS= $(patsubst %.cpp,%.o,$(SOURCES))
BIN= main

all: $(BIN)

run: $(BIN)
	./$(BIN)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN): $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	$(RM) main $(OBJECTS)

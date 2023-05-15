CXX=gcc
BIN=client

OBJECTS=client.o
INCLUDES=-I./
LIBINCLUDES=
CXXFLAGS=-Og -Wall $(INCLUDES) $(LIBINCLUDES)

all: $(BIN)

$(BIN): $(OBJECTS)	
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJECTS)

clean:
	rm -r $(OBJECTS) $(BIN) *.dSYM
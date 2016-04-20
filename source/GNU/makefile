CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=
SOURCE_DIR=..
SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS=$(patsubst $(SOURCE_DIR)/%.cpp,%.o,$(SOURCES))
EXECUTABLE=ResponseSpectrum
VPATH=$(SOURCE_DIR)

all: CFLAGS+=-O2
all: $(SOURCES) $(EXECUTABLE)

debug: CFLAGS+=-DDEBUG -D_DEBUG -g
debug: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE)

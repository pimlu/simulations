CC=em++
CFLAGS=-c -O3 -Wall -std=c++11 -s USE_SDL=2
LDFLAGS=-O3 -s USE_SDL=2
SFILES=main.cpp draw.cpp
SOURCES:=$(shell echo $(SFILES) | xargs -n1 -I% echo src/%)
OBJECTS:=$(SFILES:%.cpp=build/%.bc)
EXECUTABLE=dist/sims.html

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): mkdirs $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.bc: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@


mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -f $(EXECUTABLE) $(EXECUTABLE:.html=.js) $(EXECUTABLE).mem

CC=clang++
CFLAGS=-c -g -Wall -std=c++11
LDFLAGS:=$(shell [ "`uname`" == Darwin ] && echo -framework SDL2 || echo -lSDL2)
SFILES=main.cpp draw.cpp uitest.cpp uiwave.cpp WaveSim.cpp
SOURCES:=$(shell echo $(SFILES) | xargs -n1 -I% echo src/%)
OBJECTS:=$(SFILES:%.cpp=build/%.o)
EXECUTABLE=dist/sims

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): mkdirs $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@


mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -f $(EXECUTABLE)

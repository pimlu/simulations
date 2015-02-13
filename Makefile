CC=clang++
CFLAGS=-c -g -Wall -std=c++11
LDFLAGS:=$(shell [ "`uname`" == Darwin ] && echo -framework SDL2 -framework SDL2_ttf || echo -lSDL2 -lSDL2_ttf)
SFILES=main.cpp draw.cpp uitest.cpp uiwave.cpp WaveSim.cpp
SOURCES:=$(shell echo $(SFILES) | xargs -n1 -I% echo src/%)
OBJECTS:=$(SFILES:%.cpp=build/%.o)
EXECUTABLE=sims

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): mkdirs $(OBJECTS) | dist/data
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

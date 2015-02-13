CC=em++
CFLAGS=-c -O3 -Wall -std=c++11 -s USE_SDL=2
LDFLAGS=-O3 -s USE_SDL=2 --preload-file data
SFILES=main.cpp draw.cpp uitest.cpp uiwave.cpp WaveSim.cpp
SOURCES:=$(shell echo $(SFILES) | xargs -n1 -I% echo src/%)
OBJECTS:=$(SFILES:%.cpp=build/%.bc)
EXECUTABLE=sims.html

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): mkdirs $(OBJECTS) | dist/data
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.bc: src/%.cpp
	$(CC) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

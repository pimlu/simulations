CXX=em++
CFLAGS=-c -Wall -std=c++11 -s USE_SDL=2
LDFLAGS= -s USE_SDL=2 --preload-file data
SOURCES=$(shell find src -name "*.cpp")
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
OBJECTS:=$(SOURCES:src/%.cpp=build/%.bc)
EXECUTABLE=sims.html

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): mkdirs $(OBJECTS) | dist/data
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

build/%.bc: src/%.cpp
	$(CXX) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

CXX=em++
CFLAGS=-c -Wall -std=c++11 -s USE_SDL=2
LDFLAGS= -s USE_SDL=2 --preload-file data
SOURCES=$(shell find src -name "*.cpp")
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
OBJECTS:=$(SOURCES:src/%.cpp=build/%.bc)
EXECUTABLE=sims.html

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): $(OBJECTS) | dist/data
	@mkdir -p dist
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

build/%.bc: src/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

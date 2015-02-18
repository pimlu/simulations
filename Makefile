CFLAGS=-c -g -Wall -std=c++11
LDFLAGS:=$(shell [ "`uname`" == Darwin ] && echo -framework SDL2 -framework SDL2_ttf || echo -lSDL2 -lSDL2_ttf)
SOURCES=$(shell find src -name "*.cpp")
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE=sims

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): $(OBJECTS) | dist/data
	@mkdir -p dist
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

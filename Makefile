CFLAGS=-c -g -Wall -std=c++11
LDFLAGS:=$(shell [ "`uname`" == Darwin ] && echo -framework SDL2 -framework SDL2_ttf || echo -lSDL2 -lSDL2_ttf)
SOURCES=$(shell find src -name "*.cpp")
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
OBJECTS:=$(SOURCES:src/%.cpp=build/%.o)
EXECUTABLE=sims

all: $(SOURCES) dist/$(EXECUTABLE)

dist/$(EXECUTABLE): mkdirs $(OBJECTS) | dist/data
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	$(CXX) $(CFLAGS) $< -o $@

dist/data: data
	cp -r $< $@

mkdirs:
	@mkdir -p dist build

clean:
	rm -f $(OBJECTS)

rmdist:
	rm -rf dist/*

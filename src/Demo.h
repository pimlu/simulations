#pragma once

#include <SDL2/SDL.h>

struct Demo {
  void (*init)();
  void (*frame)();
  void (*event)(SDL_Event&);
};

#pragma once
#include "global.h"
#include "Demo.h"

namespace uitest {

extern Demo demo;

void init();
void frame();
void event(SDL_Event& e);

}

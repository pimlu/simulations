#pragma once
#include "global.h"
#include "Demo.h"

namespace uiwave {

extern Demo demo;

void init();
void frame();
void event(SDL_Event& e);


}

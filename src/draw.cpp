#include "global.h"
#include "draw.h"
#include <sstream>
#include <cstdlib>
#include <exception>
#include <algorithm>
#include <cmath>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace draw {

SDL_Window* window=nullptr;
SDL_Renderer* renderer=nullptr;

//implementation details- similar practice to what boost does
namespace detail {

//used as a wrapper to make emscripten easier
void loop() {
  static SDL_Event e;
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) std::exit(0);
    event(e);
  }
  frame();
}

}
using namespace detail;

void init(int32 w,int32 h,const char* title) {
  //initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::ostringstream out;
    out << "failed to initialize SDL.  error: " << SDL_GetError();
    throw std::runtime_error(out.str());
  }
  std::atexit(SDL_Quit);

  //create our window and renderer
  window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    w, h,
    0);
  renderer = SDL_CreateRenderer(window, -1, 0);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, FPS, 1);
#else
  while(true) {
    uint32 tstart = SDL_GetTicks();
    loop();
    int32 tdiff=SDL_GetTicks()-tstart,
      tsleep=std::max(0,(int32) (1000/FPS - tdiff));
    SDL_Delay(tsleep);
  }
#endif
}

void frame() {
  using std::sin;
  using std::cos;

  static double t=0;
  const static double dt=1.0/FPS;
  int w,h;
  size(&w,&h);

  double theta1=t;
  double theta2=t*1.618;

  setRGB(0xffffff);
  clear();
  setRGB(0xff0000);
  line(
    w*(cos(theta1)*0.8+1)/2,
    h*(sin(theta1)*0.8+1)/2,
    w*(cos(theta2)*0.8+1)/2,
    h*(sin(theta2)*0.8+1)/2);
  present();

  t+=dt;
}
void event(SDL_Event& e) {
}

void size(int* w, int* h) {
  SDL_GetWindowSize(window, w, h);
}

void clear() {
  SDL_RenderClear(renderer);
}
void present() {
  SDL_RenderPresent(renderer);
}

void setRGB(uint32 rgb) {
  setRGBA((rgb << 8) + SDL_ALPHA_OPAQUE);
}
void setRGBA(uint32 rgb) {
  fuint8 r,g,b,a;
  a=rgb%256; rgb>>=8;
  b=rgb%256; rgb>>=8;
  g=rgb%256; rgb>>=8;
  r=rgb%256;
  SDL_SetRenderDrawColor(renderer, r,g,b,a);
}

void line(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

}

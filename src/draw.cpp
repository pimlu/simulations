#include "global.h"
#include "draw.h"

#include "Demo.h"
#include "uitest.h"
#include "uiwave.h"

#include <sstream>
#include <cstdlib>
#include <exception>
#include <algorithm>


#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

namespace draw {

SDL_Window* window=nullptr;
SDL_Renderer* renderer=nullptr;
SDL_Texture* simtex = nullptr;

//implementation details- similar practice to what boost does
namespace detail {

const int FPS_SAMPLE=3*60;
//used as a wrapper to make emscripten easier
void loop() {
  static SDL_Event e;

  //simple FPS counter here
  static int count = 0;
  static uint32 tlast = SDL_GetTicks();
  if(++count == FPS_SAMPLE) {
    count = 0;
    uint32 now = SDL_GetTicks();
    cout << "FPS: " << 1000.0 * FPS_SAMPLE / (now-tlast) << endl;
    tlast = now;
  }

  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) std::exit(0);
    event(e);
  }

  frame();
}

//used to make complaining when things go wrong quicker/easier
void sdlthrow(const char* message) {
    std::ostringstream out;
    out << message << " error: " << SDL_GetError();
    throw std::runtime_error(out.str());
}

//application specific- here we decide which demo to use
Demo demos[] = {uitest::demo, uiwave::demo};
int cycle = 0, cycles = 2;

}
using namespace detail;

void init(int32 w,int32 h,const char* title) {
  //initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    sdlthrow("failed to initialize SDL.");
  }
  std::atexit(SDL_Quit);

  //create our window and renderer
  window = SDL_CreateWindow(title,
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    w, h,
    0);
  renderer = SDL_CreateRenderer(window, -1, 0);

  demos[cycle].init();

#ifdef __EMSCRIPTEN__
  //if fps is 60, we use 0 instead, which makes emscripten try to use RAF
  emscripten_set_main_loop(loop, FPS==60?0:FPS, 1);
#else
  while(true) {
    uint32 tstart = SDL_GetTicks();
    loop();
    int32 tdiff=SDL_GetTicks()-tstart,
      tsleep=std::max(0, (int32) (1000/FPS - tdiff));
    SDL_Delay(tsleep);
  }
#endif
}

//application specific- here we decide which demo to use
void frame() {
  demos[cycle].frame();
}
void event(SDL_Event& e) {
  if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
    cycle = (cycle+1)%cycles;
    demos[cycle].init();
  }
}

SDL_Point winSize() {
  SDL_Point size;
  SDL_GetWindowSize(window, &size.x, &size.y);
  return size;
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

SDL_Texture* createTex(int w, int h) {
  SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_STREAMING, w, h);
  if(tex==nullptr) {
    sdlthrow("failed to create texture.");
  }
  return tex;
}

TexData lockTex(SDL_Texture* tex) {
  TexData td;

  int err = SDL_LockTexture(tex, nullptr,
    reinterpret_cast<void **>(&td.bytes), &td.pitch);
  if(err != 0) {
    sdlthrow("failed to lock texture.");
  }
  return td;
}
void unlockTex(SDL_Texture* tex) {
  SDL_UnlockTexture(tex);
}

}

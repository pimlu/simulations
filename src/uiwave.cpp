#include "global.h"
#include "uiwave.h"
#include "draw.h"
#include "WaveSim.h"

namespace uiwave {

using namespace draw;
Demo demo = {init, frame, event};

WaveSim* ws = nullptr;
SDL_Texture* graph = nullptr;

void init() {
  SDL_DestroyTexture(graph);
  delete ws;

  cout << "doing wave equation..." << endl;

  SDL_Point size=winSize();
  int w = size.x,
    h = size.y;
  graph = createTex(w, h);

  //width, height, c, h, damp
  ws = new WaveSim(w, h, 3, 0.05, 0.0025);
}

void frame() {
  setRGB(0xffffff);
  clear();


  SDL_Point size=winSize();
  int w = size.x,
      h = size.y;

  simnum* numgraph = ws->tick(1.0/60);

  TexData td = lockTex(graph);

  //trim off 1px of edges
  for(int y=0;y<h;y++) {
    for(int x=0;x<w;x++) {
      int pos = y*td.pitch+x*4;
      int b = 256/2*(numgraph[(y+1)*(w+2)+x+1]+1);
      b=b>255?255:b;
      b=b<0?0:b;

      td.bytes[pos]=255;
      td.bytes[pos+1]=b;
      td.bytes[pos+2]=b;
      td.bytes[pos+3]=b;
    }
  }

  unlockTex(graph);

  SDL_RenderCopy(renderer, graph, nullptr, nullptr);

  present();
}

void event(SDL_Event& e) {

}

}

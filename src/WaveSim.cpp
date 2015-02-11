#include "WaveSim.h"

//make it trimmed with permanent 0s on each side for walls
WaveSim::WaveSim(int width_, int height_, simnum c_, simnum h_)
  : width(width_+2), height(height_+2), c(c_), h(h_) {

  for(int i=0;i<2;i++) waves[i] = new simnum[width*height]();

  simnum* cur = waves[cycle];
  //puts a little circle on our board
  for(int y = 1; y < height-1; y++) {
    for(int x = 1; x < width-1; x++) {
      int dx=x-width/2, dy=y-height/2;
      cur[y*width+x] = (dx*dx+dy*dy) < 1000 ? 1 : 0;
    }
  }
}

WaveSim::~WaveSim() {
  for(int i=0;i<2;i++) delete waves[i];
}

simnum WaveSim::get(simnum* state, int x, int y) {
  return state[y*width+x];
}
void WaveSim::set(simnum* state, int x, int y, simnum v) {
  state[y*width+x] = v;
}

simnum* WaveSim::getstate() {
  return waves[cycle];
}

simnum* WaveSim::tick(simnum t) {

  simnum* cur = waves[cycle];

  return cur;
}

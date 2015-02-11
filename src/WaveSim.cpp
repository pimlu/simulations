#include "WaveSim.h"
#include <cmath>

//make it trimmed with permanent 0s on each side for walls
WaveSim::WaveSim(int width_, int height_, simnum c_, simnum h_, simnum damp_)
  : width(width_+2), height(height_+2), c(c_), h(h_), damp(damp_) {


  //puts a little circle on our board.  does it to both boards to zero velocity
  for(int i=0;i<2;i++) {
    waves[i] = new simnum[width*height]();
    simnum* cur = waves[i];
    for(int y = 1; y < height-1; y++) {
      for(int x = 1; x < width-1; x++) {
        int dx=x-width/2, dy=y-height/2;
        cur[y*width+x] = 200/(1+dx*dx+dy*dy);
      }
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

simnum* WaveSim::tick(simnum dt) {
  //the most recent and second most recent states AT THE START of tick().
  //last gets overwritten with our newer stuff in this function
  simnum* cur = waves[cycle];
  simnum* last= waves[cycle=1-cycle];

  //since we use these a ton, we separate them and do it here
  simnum alpha = dt*dt * c / (h*h);
  simnum dampcur = 2 - std::pow(damp,1+dt),
    damplast = 1 - std::pow(damp,1+dt);

  for(int y = 1; y < height-1; y++) {
    for(int x = 1; x < width-1; x++) {
      //the discrete laplacian
      //the sum of the second partial derivatives on each axis
      simnum laplace =
        (-4*get(cur,x,y)
        +get(cur,x+1,y)
        +get(cur,x-1,y)
        +get(cur,x,y+1)
        +get(cur,x,y-1));
      //you can derive this using the taylor series,
      //but this is just verlet integration
      set(last,x,y,
        dampcur * get(cur,x,y)
        - damplast * get(last,x,y)
        + alpha * laplace);
    }
  }
  //last is now the newest thanks to our setting it
  return last;
}

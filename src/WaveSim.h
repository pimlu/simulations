#pragma once
#include "global.h"

using simnum = double;

class WaveSim {
  /*3 copies of the simulation specifically:
  one is present, one is past, one is working copy (tmp)
  cycles through them*/
  int cycle=0;//which one is the "present" copy
  simnum* waves[3] = {0,0,0};
  simnum get(simnum* state, int x, int y);
  void set(simnum* state, int x, int y, simnum v);
public:
  int width, height;
  simnum c, h;
  WaveSim(int width, int height, simnum c, simnum h);
  ~WaveSim();

  simnum* getstate();
  simnum* tick(simnum t);
};

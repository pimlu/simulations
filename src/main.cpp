#include "global.h"

#include "draw.h"


int main(int argc, char* argv[]) {
  cout << "press space to cycle between math demos." << endl;
  draw::init(512,512,"sims");
  return 0;
}

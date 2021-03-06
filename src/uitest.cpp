#include "global.h"
#include "uitest.h"
#include "draw.h"
#include <cmath>

namespace uitest {

using namespace draw;
Demo demo = {init, frame, event};

//the texture we use to render mandelbrot on
SDL_Texture* mandelbrot = nullptr;
//rendered text
SDL_Texture* text = nullptr;

void init() {
  SDL_DestroyTexture(mandelbrot);
  SDL_DestroyTexture(text);

  cout << "running rendering test code..." << endl;

  SDL_Point size = winSize();
  int w = size.x,
    h = size.y;

  TTF_Font* sans = openSans(24);
  text = drawText(sans, "press space to cycle demos", 0);
  TTF_CloseFont(sans);

  mandelbrot = createTex(w, h);

  TexData td = lockTex(mandelbrot);

  //mandelbrot rendering algorithm- aliased, nothing fancy
  const int ITER=50;
  //loop horizontally to be cache-friendly
  for(int y=0;y<h;y++) {
    for(int x=0;x<w;x++) {

      double a=0, b=0,
      //constants selected for positioning
      ca=x/(double)(w-1)*3 - 2.25,
      cb=y/(double)(h-1)*3 - 1.5;
      int brightness = 0;
      for(int i=0;i<ITER;i++) {
        //complex number squaring
        double tmpa = a*a - b*b + ca;
        b = 2*a*b + cb;
        a = tmpa;
        //if we know it's tending to infinity (aka, the constant term can't
        //beat the squaring term anymore) quit and choose color
        if(a*a + b*b > 4) {
          double intensity=(i+1)/(double)ITER;
          brightness=(1-intensity)*255;
          break;
        }
      }
      int pos=y*td.pitch+x*4;
      td.bytes[pos]=255;
      td.bytes[pos+1]=brightness;
      td.bytes[pos+2]=brightness;
      td.bytes[pos+3]=brightness;
    }
  }

  unlockTex(mandelbrot);
}

void frame() {
  using std::sin;
  using std::cos;
  using namespace draw;
  static double t=0;
  const static double dt=1.0/FPS;
  SDL_Point size = winSize();
  int w = size.x,
    h = size.y;

  double theta1=t;
  double theta2=t*1.618;

  setRGB(0xffffff);
  clear();

  //FIXME implement cleaner versions of these functions
  SDL_RenderCopy(renderer, mandelbrot, nullptr, nullptr);
  int tw, th;
  SDL_QueryTexture(text, nullptr, nullptr, &tw, &th);
  SDL_Rect rect = {10,0,tw,th};
  SDL_RenderCopy(renderer, text, nullptr, &rect);

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

}

#pragma once
#include "global.h"
#include <vector>
#include <SDL2/SDL.h>

#ifdef __EMSCRIPTEN__
#include <SDL/SDL_ttf.h>
#else
#include <SDL2_ttf/SDL_ttf.h>
#endif

/**
 * Represents an SDL window with some built-in draw functions.
 */
namespace draw {

/// Used to represent texture data upon locking
struct TexData {
  unsigned char* bytes = nullptr;
  int pitch = 0;
};

/// Target frames per second.
const int FPS=60;
/// Pointer to its SDL window.
extern SDL_Window* window;
/// Pointer to its SDL renderer.
extern SDL_Renderer* renderer;
/**
 * @brief Creates an SDL window/renderer.
 * @param w The window width.
 * @param h The window height.
 * @param title The window's title, shown in at the top bar.
 */
void init(int32 w, int32 h, const char* title);
/// Called FPS times per second.  Resposible for drawing.
void frame();
/// Called once for each event queued up before each frame.
void event(SDL_Event& e);
/// Gets window size and returns it as an SDL_Point.
SDL_Point winSize();
/// Must be called each frame; clears the window to the current color.
void clear();
/// Renders draw commands to the window.
void present();
/// Creates a sans serif TTF font of size pt.
TTF_Font* openSans(int pt);
/// Converts hex RGBA of the form 0xRRGGBBAA into an SDL_Color struct.
SDL_Color colorRGBA(uint32 rgba);
/**
 * @brief Renders a given string to an SDL texture.
 * @param font The font to use.
 * @param text The string to render.
 * @param color The color to render with, of the form 0xRRGGBBAA.
 */
SDL_Texture* drawText(TTF_Font* font, const char *text, uint32 color);
/**
 * @brief Sets the color to be used in drawing operations.
 * @param rgb The color, represended in hex as 0xRRGGBB.
 */
void setRGB(uint32 rgb);
/**
 * @brief Sets the color to be used in drawing operations.
 * @param rgba The color, represended in hex as 0xRRGGBBAA.
 */
void setRGBA(uint32 rgba);
/// Draws a line given a pair of coordinates.
void line(int x1, int y1, int x2, int y2);
/**
  * @brief Creates an RGBA8888 streaming texture.
  * @param w The texture width.
  * @param h The texture height.
 */
SDL_Texture* createTex(int w, int h);
/**
  * @brief Creates an RGBA8888 streaming texture from a surface.
  * @param surf The surface
 */
SDL_Texture* createTex(SDL_Surface* surf);
/**
 * @brief Locks a given texture, allowing direct writing.
 * @param tex The pointer to the texture to lock.
 * @return A TexData struct containing a pointer to the bytes to write to and the pitch of each row.
 */
TexData lockTex(SDL_Texture* tex);
/**
 * @brief Unlocks a texture, making it usable for rendering again.
 * @param tex The texture to unlock.
 */
void unlockTex(SDL_Texture* tex);

}

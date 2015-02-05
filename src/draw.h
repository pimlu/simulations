#pragma once
#include "global.h"
#include <vector>
#include <SDL2/SDL.h>
/**
 * Represents an SDL window with some built-in draw functions.
 */
namespace draw {

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
/// Gets window size and stores it to width and height pointers.
void size(int* w, int* h);
/// Must be called each frame; clears the window to the current color.
void clear();
/// Renders draw commands to the window.
void present();
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
};

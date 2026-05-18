#include "renderer/framebuffer.h"

#include <cstdint>
#include <cstdlib>
#include <cstring>

static uint32_t* s_pixels = nullptr;
static int s_width = 0;
static int s_height = 0;

void Framebuffer_Init(int width, int height) {
  s_width = width;
  s_height = height;
  s_pixels = new uint32_t[width * height];
  memset(s_pixels, 0, width * height * sizeof(uint32_t));
}

void Framebuffer_Shutdown() { delete[] s_pixels; }

void Framebuffer_SetPixel(int x, int y, uint32_t color) {
  if (x < 0 || x >= s_width || y < 0 || y >= s_height) return;
  s_pixels[y * s_width + x] = color;
}

uint32_t* Framebuffer_GetPixels() { return s_pixels; }

void Framebuffer_DrawLine(int x0, int y0, int x1, int y1, uint32_t color) {
  int dx = abs(x1 - x0), dy = abs(y1 - y0);
  int sx = x0 < x1 ? 1 : -1;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx - dy;

  while (true) {
    Framebuffer_SetPixel(x0, y0, color);
    if (x0 == x1 && y0 == y1) break;
    int e2 = 2 * err;
    if (e2 > -dy) {
      err -= dy;
      x0 += sx;
    }
    if (e2 < dx) {
      err += dx;
      y0 += sy;
    }
  }
}

void Framebuffer_Clear() {
  memset(s_pixels, 0, s_width * s_height * sizeof(uint32_t));
}

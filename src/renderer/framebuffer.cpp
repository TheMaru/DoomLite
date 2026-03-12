#include "renderer/framebuffer.h"
#include <cstdint>
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

void Framebuffer_Shutdown() {
  delete[] s_pixels;
}

void Framebuffer_SetPixel(int x, int y, uint32_t color) {
  if (x < 0 || x >= s_width || y < 0 || y >= s_height) return;
  s_pixels[y * s_width + x] = color;
}

uint32_t* Framebuffer_GetPixels() {
  return s_pixels;
}

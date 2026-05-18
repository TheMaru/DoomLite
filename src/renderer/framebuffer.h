#pragma once
#include <cstdint>

void Framebuffer_Init(int width, int height);
void Framebuffer_Shutdown();
void Framebuffer_SetPixel(int x, int y, uint32_t color);
uint32_t* Framebuffer_GetPixels();
void Framebuffer_DrawLine(int x0, int y0, int x1, int y1, uint32_t color);
void Framebuffer_Clear();

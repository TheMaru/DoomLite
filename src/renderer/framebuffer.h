#pragma once
#include <cstdint>

void Framebuffer_Init(int width, int height);
void Framebuffer_Shutdown();
void Framebuffer_SetPixel(int x, int y, uint32_t color);
uint32_t* Framebuffer_GetPixels();

#pragma once
#include <cstdint>

bool Platform_Init(int width, int height, const char* title);
void Platform_Shutdown();
void Platform_PollEvents();
void Platform_Present(const uint32_t* framebuffer);
bool Platform_ShouldQuit();

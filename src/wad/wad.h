#pragma once
#include <cstdint>

struct Lump {
  uint8_t* data;
  int32_t size;
};

bool WAD_Init(const char* path);
void WAD_Shutdown();
Lump WAD_GetLump(const char* name);

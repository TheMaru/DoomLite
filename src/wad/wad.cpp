#include "wad/wad.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

struct WadHeader {
  char magic[4];
  int32_t num_lumps;
  int32_t dir_offset;
};

struct LumpInfo {
  int32_t offset;
  int32_t size;
  char name[8];
};

static FILE* s_file = nullptr;
static LumpInfo* s_directory = nullptr;
static int32_t s_numlumps = 0;

bool WAD_Init(const char* path) {
  s_file = fopen(path, "rb");
  if (s_file == nullptr) return false;

  WadHeader header;
  fread(&header, sizeof(WadHeader), 1, s_file);
  if (strncmp(header.magic, "IWAD", 4) != 0 &&
      strncmp(header.magic, "PWAD", 4) != 0) {
    fclose(s_file);
    return false;
  };

  fseek(s_file, header.dir_offset, SEEK_SET);
  s_directory = new LumpInfo[header.num_lumps];
  fread(s_directory, sizeof(LumpInfo), header.num_lumps, s_file);
  s_numlumps = header.num_lumps;
  return true;
}

void WAD_Shutdown() {
  delete[] s_directory;
  fclose(s_file);
}

Lump WAD_GetLump(const char* name) {
  Lump lump = {nullptr, 0};

  for (int i = 0; i < s_numlumps; i++) {
    if (strncmp(s_directory[i].name, name, 8) == 0) {
      fseek(s_file, s_directory[i].offset, SEEK_SET);
      lump.data = new uint8_t[s_directory[i].size];
      lump.size = s_directory[i].size;
      fread(lump.data, 1, lump.size, s_file);
      break;
    }
  }
  return lump;
}

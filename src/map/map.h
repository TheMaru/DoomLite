#pragma once

#include <cstdint>

constexpr uint16_t NODE_SUBSECTOR = 0x8000;

struct Vertex {
  int16_t x;
  int16_t y;
};

struct LineDef {
  uint16_t v1;
  uint16_t v2;
  uint16_t flags;
  uint16_t special;
  uint16_t tag;
  uint16_t sidedef_r;
  uint16_t sidedef_l;
};

struct SideDef {
  int16_t x_offset;
  int16_t y_offset;
  char upper_tex[8];
  char lower_tex[8];
  char mid_tex[8];
  uint16_t sector;
};

struct Sector {
  int16_t floor_height;
  int16_t ceil_height;
  char floor_tex[8];
  char ceil_tex[8];
  int16_t light;
  uint16_t special;
  uint16_t tag;
};

struct Thing {
  int16_t x;
  int16_t y;
  uint16_t angle;
  uint16_t type;
  uint16_t flags;
};

struct Node {
  int16_t x;
  int16_t y;
  int16_t dx;
  int16_t dy;
  int16_t bbox[2][4];    // bounding boxes [front/back][top/bottom/left/right]
  uint16_t children[2];  // child indices - front [0], back [1]
};

struct SSector {
  uint16_t num_segs;
  uint16_t first_seg;
};

struct Seg {
  uint16_t v1;
  uint16_t v2;
  int16_t angle;
  uint16_t linedef;
  uint16_t side;
  int16_t offset;
};

struct Map {
  Vertex* vertices;
  int num_vertices;
  LineDef* linedefs;
  int num_linedefs;
  SideDef* sidedefs;
  int num_sidedefs;
  Sector* sectors;
  int num_sectors;
  Thing* things;
  int num_things;
  Node* nodes;
  int num_nodes;
  SSector* ssectors;
  int num_ssectors;
  Seg* segs;
  int num_segs;
};

Map* Map_Load(const char* name);
void Map_Unload(Map* map);

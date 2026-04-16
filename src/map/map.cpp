#include "map/map.h"

#include <cstring>

#include "wad/wad.h"

Map* Map_Load(
    const char* name) {  // TODO: parameter not used now, will be done when
                         // proper map marker searching will be implemented
  Map* map = new Map();

  Lump vertices_lump = WAD_GetLump("VERTEXES");
  map->num_vertices = vertices_lump.size / sizeof(Vertex);
  map->vertices = new Vertex[map->num_vertices];
  memcpy(map->vertices, vertices_lump.data, vertices_lump.size);
  delete[] vertices_lump.data;

  Lump linedefs_lump = WAD_GetLump("LINEDEFS");
  map->num_linedefs = linedefs_lump.size / sizeof(LineDef);
  map->linedefs = new LineDef[map->num_linedefs];
  memcpy(map->linedefs, linedefs_lump.data, linedefs_lump.size);
  delete[] linedefs_lump.data;

  Lump sidedefs_lump = WAD_GetLump("SIDEDEFS");
  map->num_sidedefs = sidedefs_lump.size / sizeof(SideDef);
  map->sidedefs = new SideDef[map->num_sidedefs];
  memcpy(map->sidedefs, sidedefs_lump.data, sidedefs_lump.size);
  delete[] sidedefs_lump.data;

  Lump sectors_lump = WAD_GetLump("SECTORS");
  map->num_sectors = sectors_lump.size / sizeof(Sector);
  map->sectors = new Sector[map->num_sectors];
  memcpy(map->sectors, sectors_lump.data, sectors_lump.size);
  delete[] sectors_lump.data;

  Lump things_lump = WAD_GetLump("THINGS");
  map->num_things = things_lump.size / sizeof(Thing);
  map->things = new Thing[map->num_things];
  memcpy(map->things, things_lump.data, things_lump.size);
  delete[] things_lump.data;

  Lump nodes_lump = WAD_GetLump("NODES");
  map->num_nodes = nodes_lump.size / sizeof(Node);
  map->nodes = new Node[map->num_nodes];
  memcpy(map->nodes, nodes_lump.data, nodes_lump.size);
  delete[] nodes_lump.data;

  Lump ssectors_lump = WAD_GetLump("SSECTORS");
  map->num_ssectors = ssectors_lump.size / sizeof(SSector);
  map->ssectors = new SSector[map->num_ssectors];
  memcpy(map->ssectors, ssectors_lump.data, ssectors_lump.size);
  delete[] ssectors_lump.data;

  Lump segs_lump = WAD_GetLump("SEGS");
  map->num_segs = segs_lump.size / sizeof(Seg);
  map->segs = new Seg[map->num_segs];
  memcpy(map->segs, segs_lump.data, segs_lump.size);
  delete[] segs_lump.data;

  return map;
}

void Map_Unload(Map* map) {
  delete[] map->vertices;
  delete[] map->linedefs;
  delete[] map->sidedefs;
  delete[] map->sectors;
  delete[] map->things;
  delete[] map->nodes;
  delete[] map->ssectors;
  delete[] map->segs;
  delete map;
}

Thing* Map_FindThing(const Map* map, ThingType type) {
  for (int i = 0; i < map->num_things; i++) {
    if (map->things[i].type == type) {
      return &map->things[i];
    }
  }
  return nullptr;
}

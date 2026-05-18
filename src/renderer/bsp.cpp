#include "renderer/bsp.h"

#include "map/map.h"
#include "renderer/segs.h"

void BSP_Render(const Map* map, int node_index, const Player* player) {
  if (node_index & NODE_SUBSECTOR) {
    int ssector_index = node_index & ~NODE_SUBSECTOR;
    SSector ssector = map->ssectors[ssector_index];
    for (int i = 0; i < ssector.num_segs; i++) {
      const Seg* seg = &map->segs[ssector.first_seg + i];
      RenderSeg(map, seg, player);
    }
    return;
  }

  Node node = map->nodes[node_index];
  // side > 0 -> player on front (left), children[0]
  // side <= 0 -> player is on back (right), children[1]
  int side = (player->x - node.x) * node.dy - (player->y - node.y) * node.dx;

  if (side > 0) {
    BSP_Render(map, node.children[0], player);
    BSP_Render(map, node.children[1], player);
  } else {
    BSP_Render(map, node.children[1], player);
    BSP_Render(map, node.children[0], player);
  }
}

#include "renderer/bsp.h"

#include <cstdio>

#include "map/map.h"

void BSP_Render(const Map* map, int node_index, int player_x, int player_y) {
  if (node_index & NODE_SUBSECTOR) {
    int ssector_index = node_index & ~NODE_SUBSECTOR;
    printf("subsector with index %d will be rendered\n", ssector_index);
    return;
  }

  Node node = map->nodes[node_index];
  // side > 0 -> player on front (left), children[0]
  // side <= 0 -> player is on back (right), children[1]
  int side = (player_x - node.x) * node.dy - (player_y - node.y) * node.dx;

  if (side > 0) {
    BSP_Render(map, node.children[0], player_x, player_y);
    BSP_Render(map, node.children[1], player_x, player_y);
  } else {
    BSP_Render(map, node.children[1], player_x, player_y);
    BSP_Render(map, node.children[0], player_x, player_y);
  }
}

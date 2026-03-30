#include "renderer/automap.h"

#include <algorithm>

#include "constants.h"
#include "map/map.h"
#include "renderer/framebuffer.h"

using std::min;

void Automap_Render(const Map* map) {
  int max_x = map->vertices[0].x, min_x = map->vertices[0].x,
      max_y = map->vertices[0].y, min_y = map->vertices[0].y;
  for (int i = 1; i < map->num_vertices; i++) {
    Vertex v = map->vertices[i];
    if (v.x > max_x) max_x = v.x;
    if (v.x < min_x) min_x = v.x;
    if (v.y > max_y) max_y = v.y;
    if (v.y < min_y) min_y = v.y;
  }

  int map_width = max_x - min_x;
  int map_height = max_y - min_y;

  constexpr int padding = 20;
  float scale = min((float)(SCREEN_WIDTH - padding * 2) / map_width,
                    (float)(SCREEN_HEIGHT - padding * 2) / map_height);
  for (int i = 0; i < map->num_linedefs; i++) {
    Vertex v1 = map->vertices[map->linedefs[i].v1];
    Vertex v2 = map->vertices[map->linedefs[i].v2];
    int screen_x1 = (v1.x - min_x) * scale + padding;
    int screen_y1 = SCREEN_HEIGHT - (v1.y - min_y) * scale - padding;
    int screen_x2 = (v2.x - min_x) * scale + padding;
    int screen_y2 = SCREEN_HEIGHT - (v2.y - min_y) * scale - padding;
    Framebuffer_DrawLine(screen_x1, screen_y1, screen_x2, screen_y2,
                         0xFF00FF00);
  }
}

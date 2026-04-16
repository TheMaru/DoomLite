#include "renderer/automap.h"

#include <algorithm>
#include <cassert>

#include "constants.h"
#include "map/map.h"
#include "renderer/framebuffer.h"

using std::min;

constexpr uint32_t RED = 0xFFFF0000;
constexpr uint32_t BROWN = 0xFFAA6622;
// constexpr uint32_t YELLOW = 0xFFFFFF00;
constexpr uint32_t WHITE = 0xFFFFFFFF;

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
    LineDef linedef = map->linedefs[i];
    Vertex v1 = map->vertices[linedef.v1];
    Vertex v2 = map->vertices[linedef.v2];
    int screen_x1 = (v1.x - min_x) * scale + padding;
    int screen_y1 = SCREEN_HEIGHT - (v1.y - min_y) * scale - padding;
    int screen_x2 = (v2.x - min_x) * scale + padding;
    int screen_y2 = SCREEN_HEIGHT - (v2.y - min_y) * scale - padding;
    bool two_sided = (linedef.sidedef_l != 0xFFFF);

    Framebuffer_DrawLine(screen_x1, screen_y1, screen_x2, screen_y2,
                         two_sided ? BROWN : RED);
  }

  // draw player starting position
  Thing* player = Map_FindThing(map, THING_PLAYER1_START);
  assert(player != nullptr);
  int length = 5;
  int screen_x = (player->x - min_x) * scale + padding;
  int screen_x1 = screen_x - length;
  int screen_x2 = screen_x + length;
  int screen_y = SCREEN_HEIGHT - (player->y - min_y) * scale - padding;
  int screen_y1 = screen_y + length;
  int screen_y2 = screen_y - length;
  Framebuffer_DrawLine(screen_x1, screen_y, screen_x2, screen_y, WHITE);
  Framebuffer_DrawLine(screen_x, screen_y1, screen_x, screen_y2, WHITE);
}

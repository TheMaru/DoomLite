#include "renderer/segs.h"

#include <algorithm>
#include <cmath>

#include "constants.h"
#include "renderer/framebuffer.h"

static bool s_occluded[SCREEN_WIDTH] = {false};

constexpr float NEAR_PLANE = 1.0f;

void RenderSeg(const Map *map, const Seg *seg, const Player *player) {
  Vertex world_v1 = map->vertices[seg->v1];
  Vertex world_v2 = map->vertices[seg->v2];

  float dx1 = world_v1.x - player->x;
  float dy1 = world_v1.y - player->y;
  float dx2 = world_v2.x - player->x;
  float dy2 = world_v2.y - player->y;

  float angle_rad = player->angle * M_PI / 180.0f;
  float cos_a = cosf(angle_rad);
  float sin_a = sinf(angle_rad);

  float view_x1 = dx1 * sin_a - dy1 * cos_a;
  float view_y1 = dx1 * cos_a + dy1 * sin_a;
  float view_x2 = dx2 * sin_a - dy2 * cos_a;
  float view_y2 = dx2 * cos_a + dy2 * sin_a;

  if (view_y1 <= 0 && view_y2 <= 0)
    return;

  if (view_y1 <= 0 || view_y2 <= 0) {
    float t = (NEAR_PLANE - view_y1) / (view_y2 - view_y1);
    float clipped_x = view_x1 + t * (view_x2 - view_x1);

    if (view_y1 <= 0) {
      view_x1 = clipped_x;
      view_y1 = NEAR_PLANE;
    } else {
      view_x2 = clipped_x;
      view_y2 = NEAR_PLANE;
    }
  }

  constexpr float FOV_SCALE = SCREEN_WIDTH / 2.0f;

  float inv_y1 = 1.0f / view_y1;
  float inv_y2 = 1.0f / view_y2;

  float screen_x1 = (view_x1 / view_y1) * FOV_SCALE + SCREEN_WIDTH / 2.0f;
  float screen_x2 = (view_x2 / view_y2) * FOV_SCALE + SCREEN_WIDTH / 2.0f;

  int x1 = (int)screen_x1;
  int x2 = (int)screen_x2;

  if (x1 >= x2)
    return;
  if (x2 < 0 || x1 >= SCREEN_WIDTH)
    return;

  x1 = std::max(x1, 0);
  x2 = std::min(x2, SCREEN_WIDTH - 1);

  constexpr float WALL_HEIGHT = 128.0f;

  uint32_t color = 0xFF000000 | ((seg - map->segs) * 12345678);

  for (int x = x1; x <= x2; x++) {
    if (s_occluded[x])
      continue;

    float t = (float)(x - x1) / (float)(x2 - x1);
    float inv_y = inv_y1 + t * (inv_y2 - inv_y1);
    float view_y = 1.0f / inv_y;

    if (view_y <= 0.0f)
      continue;

    int half_height = (int)(WALL_HEIGHT / view_y * FOV_SCALE);
    int top = SCREEN_HEIGHT / 2 - half_height;
    int bottom = SCREEN_HEIGHT / 2 + half_height;

    top = std::max(top, 0);
    bottom = std::min(bottom, SCREEN_HEIGHT - 1);

    Framebuffer_DrawLine(x, top, x, bottom, color);
    s_occluded[x] = true;
  }
}

void ClearOcclusion() { memset(s_occluded, 0, sizeof(s_occluded)); }

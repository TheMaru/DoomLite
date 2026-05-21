#include <cassert>
#include <cstdio>

#include "constants.h"
#include "game/player.h"
#include "map/map.h"
#include "platform/platform.h"
#include "renderer/automap.h"
#include "renderer/bsp.h"
#include "renderer/framebuffer.h"
#include "renderer/segs.h"
#include "wad/wad.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("Usage: DoomLite <path/to/doom.wad>\n");
    return 1;
  }

  if (!WAD_Init(argv[1])) {
    printf("Failed to load WAD\n");
    return 1;
  }

  Map* map = Map_Load("E1M1");

  if (!Platform_Init(SCREEN_WIDTH, SCREEN_HEIGHT, "DoomLite")) {
    return 1;
  }

  Framebuffer_Init(SCREEN_WIDTH, SCREEN_HEIGHT);
  Automap_Render(map);

  Player player;
  Player_Init(&player, map);

  while (!Platform_ShouldQuit()) {
    Platform_PollEvents();
    Framebuffer_Clear();
    ClearOcclusion();
    BSP_Render(map, map->num_nodes - 1, &player);
    Platform_Present(Framebuffer_GetPixels());
  }

  Map_Unload(map);
  WAD_Shutdown();
  Framebuffer_Shutdown();
  Platform_Shutdown();
  return 0;
}

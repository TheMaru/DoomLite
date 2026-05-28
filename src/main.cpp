#include <cassert>
#include <cstdio>

#include "SDL2/SDL_timer.h"
#include "constants.h"
#include "game/player.h"
#include "map/map.h"
#include "platform/platform.h"
#include "renderer/automap.h"
#include "renderer/bsp.h"
#include "renderer/framebuffer.h"
#include "renderer/segs.h"
#include "wad/wad.h"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Usage: DoomLite <path/to/doom.wad>\n");
    return 1;
  }

  if (!WAD_Init(argv[1])) {
    printf("Failed to load WAD\n");
    return 1;
  }

  Map *map = Map_Load("E1M1");

  if (!Platform_Init(SCREEN_WIDTH, SCREEN_HEIGHT, "DoomLite")) {
    return 1;
  }

  Framebuffer_Init(SCREEN_WIDTH, SCREEN_HEIGHT);
  Automap_Render(map);

  Player player;
  Player_Init(&player, map);

  uint32_t last_time = SDL_GetTicks();

  while (!Platform_ShouldQuit()) {
    uint32_t current_time = SDL_GetTicks();
    float dt = (current_time - last_time) / 1000.0f;
    last_time = current_time;

    Platform_PollEvents();
    Player_Update(&player, dt);
    Framebuffer_Clear();
    ClearOcclusion();
    BSP_Render(map, map->num_nodes - 1, &player);
    Platform_Present(Framebuffer_GetPixels());

    // cap to ~60fps
    uint32_t frame_time = SDL_GetTicks() - current_time;
    if (frame_time < 16) {
      SDL_Delay(16 - frame_time);
    }
  }

  Map_Unload(map);
  WAD_Shutdown();
  Framebuffer_Shutdown();
  Platform_Shutdown();
  return 0;
}

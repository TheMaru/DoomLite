#include <cstdio>

#include "map/map.h"
#include "platform/platform.h"
#include "renderer/framebuffer.h"
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
  printf("Vertices: %d\n", map->num_vertices);
  printf("Linedefs: %d\n", map->num_linedefs);
  printf("Sidedefs: %d\n", map->num_sidedefs);
  printf("Sectors: %d\n", map->num_sectors);

  Map_Unload(map);
  WAD_Shutdown();

  if (!Platform_Init(800, 600, "DoomLite")) {
    return 1;
  }

  Framebuffer_Init(800, 600);

  Framebuffer_DrawLine(10, 20, 700, 20, 0xFF00FF00);

  while (!Platform_ShouldQuit()) {
    Platform_PollEvents();
    Platform_Present(Framebuffer_GetPixels());
  }

  Framebuffer_Shutdown();
  Platform_Shutdown();
  return 0;
}

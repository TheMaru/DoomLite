#include "platform/platform.h"
#include "renderer/framebuffer.h"

int main() {
  if (!Platform_Init(800, 600, "DoomLite")) {
    return 1;
  }

  Framebuffer_Init(800, 600);

  while (!Platform_ShouldQuit()) {
    Platform_PollEvents();
    Platform_Present(Framebuffer_GetPixels());
  }

  Framebuffer_Shutdown();
  Platform_Shutdown();
  return 0;
}

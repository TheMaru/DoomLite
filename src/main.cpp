#include "platform/platform.h"

int main() {
  if (!Platform_Init(800, 600, "DoomLite")) {
    return 1;
  }

  while (!Platform_ShouldQuit()) {
    Platform_PollEvents();
    Platform_Present(nullptr);
  }
  Platform_Shutdown();
  return 0;
}

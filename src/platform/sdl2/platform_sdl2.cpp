#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "platform/platform.h"
#include <SDL2/SDL.h>

static SDL_Window*   s_window   = nullptr;
static SDL_Renderer* s_renderer = nullptr;
static bool          s_quit     = false;
static SDL_Texture*  s_texture  = nullptr;
static int s_width = 0;
static int s_height = 0;

bool Platform_Init(int width, int height, const char* title) {
  s_width = width;
  s_height = height;
  
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    return false;
  }

  s_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
  if (s_window == nullptr) return false;

  s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_ACCELERATED);
  if (s_renderer == nullptr) return false;

  s_texture = SDL_CreateTexture(s_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

  return true;
}

void Platform_Shutdown() {
  SDL_DestroyTexture(s_texture);
  SDL_DestroyRenderer(s_renderer);
  SDL_DestroyWindow(s_window);
  SDL_Quit();
}

void Platform_PollEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        s_quit = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
          s_quit = true;
        break;
    }
  }
}

void Platform_Present(const uint32_t* framebuffer) {
  if (framebuffer) {
    SDL_UpdateTexture(s_texture, nullptr, framebuffer, s_width * (int)sizeof(uint32_t));
    SDL_RenderCopy(s_renderer, s_texture, nullptr, nullptr);
  } else {
    SDL_SetRenderDrawColor(s_renderer, 0, 0, 0, 255);
    SDL_RenderClear(s_renderer);
  }
  SDL_RenderPresent(s_renderer);
}

bool Platform_ShouldQuit() {
  return s_quit;
}

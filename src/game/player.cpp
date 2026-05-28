#include "game/player.h"

#include <SDL2/SDL.h>
#include <cassert>
#include <cmath>

#include "map/map.h"

constexpr float MOVE_SPEED = 200.0f;
constexpr float ROTATION_SPEED = 90.0f;

void Player_Init(Player *player, const Map *map) {
  Thing *start = Map_FindThing(map, THING_PLAYER1_START);
  assert(start != nullptr);
  player->x = start->x;
  player->y = start->y;
  player->angle = (float)start->angle;
}

void Player_Update(Player *player, float delta_time) {
  const Uint8 *keys = SDL_GetKeyboardState(nullptr);

  if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
    float angle_rad = player->angle * M_PI / 180.0f;
    player->x += cosf(angle_rad) * MOVE_SPEED * delta_time;
    player->y += sinf(angle_rad) * MOVE_SPEED * delta_time;
  }
  if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
    float angle_rad = player->angle * M_PI / 180.0f;
    player->x -= cosf(angle_rad) * MOVE_SPEED * delta_time;
    player->y -= sinf(angle_rad) * MOVE_SPEED * delta_time;
  }
  if (keys[SDL_SCANCODE_A] || keys[SDL_SCANCODE_LEFT]) {
    player->angle += ROTATION_SPEED * delta_time;
  }
  if (keys[SDL_SCANCODE_D] || keys[SDL_SCANCODE_RIGHT]) {
    player->angle -= ROTATION_SPEED * delta_time;
  }

  if (player->angle >= 360.0f)
    player->angle -= 360.0f;
  if (player->angle < 0.0f)
    player->angle += 360.0f;
}

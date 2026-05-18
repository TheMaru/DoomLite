#include "game/player.h"

#include <cassert>

#include "map/map.h"

void Player_Init(Player* player, const Map* map) {
  Thing* start = Map_FindThing(map, THING_PLAYER1_START);
  assert(start != nullptr);
  player->x = start->x;
  player->y = start->y;
  player->angle = (float)start->angle;
}

void Player_Update(Player* player) {}

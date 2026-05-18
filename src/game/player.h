#pragma once

#include "map/map.h"

struct Player {
  float x;
  float y;
  float angle;
};

void Player_Init(Player* player, const Map* map);

void Player_Update(Player* player);

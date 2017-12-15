#ifndef PLAYER_H
#define PLAYER_H

#include"SFML/Graphics.hpp"
#include"Bullet.h"

using namespace sf;

class Player
{
public:
          Sprite body;
          Texture *texture;
          int Life;
          int LifeMax;
          std::vector<Bullet> bullets;
          Player(Texture *texture);
};

#endif

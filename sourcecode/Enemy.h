#ifndef ENEMY_H
#define ENEMY_H
#include"SFML/Graphics.hpp"

using namespace sf;

class Enemy
{
public:
          Sprite body;

          int Life;
          int LifeMax;

          Enemy(Texture *texture, Vector2u windowSize);

};

#endif

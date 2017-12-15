#ifndef BULLET_H
#define BULLET_H

#include"SFML/Graphics.hpp"

using namespace sf;

class Bullet
{
public:
          Sprite bullet;
          Bullet(Texture *texture, Vector2f pos);

};

#endif

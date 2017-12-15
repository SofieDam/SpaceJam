#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Bullet.h"

using namespace sf;

Bullet::Bullet(Texture *texture, Vector2f pos)
{
    this->bullet.setTexture(*texture);
    this->bullet.setScale(0.05f, 0.05f);
    this->bullet.setPosition(pos);
}


// Bullet::~Bullet()
// {
//
// }

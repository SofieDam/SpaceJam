#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Enemy.h"

using namespace sf;

Enemy::Enemy(Texture *texture, Vector2u windowSize)
{
    this->LifeMax = 1;
    this->Life = this->LifeMax;
    this->body.setTexture(*texture);
    this->body.setScale(0.3f, 0.3f);
    this->body.setPosition(rand()% (int)(windowSize.x  - this->body.getGlobalBounds().width),
                                              0.f - this->body.getGlobalBounds().height);
}

//~Enemy(){}

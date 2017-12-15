#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Player.h"

using namespace sf;

Player::Player(Texture *texture)
{
		this->LifeMax = 1;
		this->Life = this->LifeMax;

		this->texture = texture;
		this->body.setTexture(*texture);
		this->body.setScale(0.30f, 0.30f);
		this->body.setPosition(400.f , 520.f);
}

//~Player() {}

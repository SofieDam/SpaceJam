/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Collision.cpp
 * Enhetsnamn: Collision
 * Typ:        Definitioner hörande till modul Collision
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil hanterar nästan allt som har med spelskärmen att
 * göra. Spelarens och objektens (fiendeskepp samt asteroid) rörelse på
 * spelskärmen så man inte hamnar utanför spelplanen (800 width, 600 heigth), skott
 * från både skepp och fiendeskepp. 
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<math.h>
#include<cstdlib>
#include<vector>
#include<string>
#include<memory>
#include<utility>
#include <fstream>
#include "Object.h"
#include "Pause.h"


using namespace sf;



/* -------------  Object  -------------- */

void Object::destroy()
{
  destroyed = true;
}

bool Object::is_destroyed()
{
  return destroyed;
}

sf::Sprite Object::get_body()
{
  return  body;
}

int Object::get_val()
{
  return val;
}

void Object::set_val(int i)
{
  val = i;
}

void Object::set_position(Vector2f pos)
{
  body.setPosition(pos);
}



/* -------------  Player  -------------- */

void Player::collide(std::unique_ptr<Object>& other)
{
  if (typeid(*other) != typeid(Friendly_Bullet))
  {
    if (HP > 1)
    {
      HP--;
    }
    else
    {
      destroyed = true;
    }
  }
}

void Player::move()
{
  if (Keyboard::isKeyPressed(Keyboard::Left))
  {
    body.move(-12.f,0.f);
  }
  else if (Keyboard::isKeyPressed(Keyboard::Right))
  {
    body.move(12.f,0.f);
  }
}

bool Player::shoot()
{
  if (shoot_timer < 10)
  {
    shoot_timer++;
  }
  /* Shoot controls */
  if (Keyboard::isKeyPressed(Keyboard::Space) && shoot_timer >= 10)
  {
    shoot_timer = 0; /* reset timer */
    return true;
  }
  return false;
}

/* -------------  Objekt  -------------- */

void Obstacle::collide(std::unique_ptr<Object>& other)
{
  if (typeid(*other) == typeid(Player) ||typeid(*other) == typeid(Friendly_Bullet))
  {
    destroyed = true;
  }
}

void Obstacle::move()
{
  body.move(0.f, 6.f);
}

bool Obstacle::shoot()
{
  return false;
}


/* -------------  Fiende  -------------- */

bool Enemy::shoot()
{
  if (phase == 1)
  {
    if (salvo_timer >= 100)
    {
      if (shoot_timer == 15)
      {
        shoot_timer = 0;
        shot_counter++;
        if (shot_counter == 3)
        {
          shot_counter = 0;
          salvo_timer = 0;
          salvo_counter++;
        }
        return true;
      }
      if (salvo_counter >= 5)
      {
        phase++;
      }
      shoot_timer++;
    }
    salvo_timer++;
  }
  return false;
}

void Enemy::move()
{
  if (phase == 0)
  {
    if (body.getPosition().y >= 150)
    {
      phase++;
    }
    body.move(0.f, 3.f);
  }
  else if (phase == 2)
  {
    if (body.getPosition().x > 400 - (body.getGlobalBounds().width / 2))
    {
      body.move(4.f, 0.f);
    }
    else
    {
      body.move(-4.f, 0.f);
    }
  }
}


/* -------------  Asteroid  -------------- */

void Asteroid::move()
{
  body.move(0.f, 5.f);
}


/* -------------  Enemy bullet  -------------- */

void Enemy_Bullet::move()
{
  body.move(0.f, 10.f);
}

void Enemy_Bullet::collide(std::unique_ptr<Object>& other)
{
  if (typeid(*other) == typeid(Player))
  {
    destroyed = true;
  }
}


/* -------------  Friendly bullet  -------------- */

void Friendly_Bullet::collide(std::unique_ptr<Object>& other)
{
  if (typeid(*other) == typeid(Enemy) || typeid(*other) == typeid(Asteroid))
  {
    destroyed = true;
  }
}

void Friendly_Bullet::move()
{
  body.move(0.f, -10.f);
}

bool Friendly_Bullet::shoot()
{
  return false;
}

/*
 * SLUT PÅ FILEN Collision.cpp
 */

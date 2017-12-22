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
 * från både skepp och fiendeskepp. Kollar kollision mellan alla spelareskepp
 * och objekten. Hanterar hur snabt fiendeskepp och asteroider ska spawna.
 * Hanterar poäng och skriver ut det på skärmen
 * och sparar dessa i en text-fil. 
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



/* -------------  World  -------------- */

World::World(Font& font)
  : score{0}, enemySpawnTimer{0}, asteroidSpawnTimer{0}, game_paused{false}
{
    playerTex.loadFromFile("Sprites/player.png");
    enemyTex.loadFromFile("Sprites/enemy.png");
    asteroidTex.loadFromFile("Sprites/asteroid.png");
    bulletTex.loadFromFile("Sprites/bullet.png");
    backgroundTex.loadFromFile("Sprites/starbackg.png");

    scoreText.setFont(font);
    scoreText.setString(ssScore.str());
    scoreText.setCharacterSize(20);
    scoreText.setColor(Color::White);
    scoreText.setPosition(10.f, 10.f);

    sprites.push_back(std::move(std::unique_ptr<Player> {new Player(&playerTex)}));
    background.setTexture(backgroundTex);

    update_score(0);

    std::ifstream readFile;
    readFile.open("gamedata/scores.txt");
    if (readFile.is_open())
    {
        while (!readFile.eof())
        {
          readFile >> highscore0
                   >> highscore1
                   >> highscore2
                   >> highscore3
                   >> highscore4;
        }
    }
    readFile.close();

}



void World::update_score(int const i)
{
  score += sprites[i]->get_val();
  ssScore.str("");
  ssScore << "Score " << score;
  scoreText.setString(ssScore.str());

}



void World::remove_from_list(long unsigned& m)
{
  sprites.erase(sprites.begin() + m);
}



void World::move_sprites()
{
  for (size_t i=0; i < sprites.size(); i++) /* sprites rörelse */
  {
      sprites[i]->move();

      /* Hantera fönsterkanten (ej player) */
      if (sprites[i]->get_body().getPosition().y > 600 || sprites[i]->get_body().getPosition().y < 0 - sprites[i]->get_body().getGlobalBounds().height
          || sprites[i]->get_body().getPosition().x < 0 - sprites[i]->get_body().getGlobalBounds().width || sprites[i]->get_body().getPosition().x > 800)
      {
        sprites[i]->set_val(0);
        sprites[i]->destroy();
      }
  }
  /* Hantera fönsterkanten för player */
  if (sprites[0]->get_body().getPosition().x > 800 - sprites[0]->get_body().getGlobalBounds().width)
  {
    sprites[0]->set_position(Vector2f(800 - sprites[0]->get_body().getGlobalBounds().width, sprites[0]->get_body().getPosition().y));
  }
  else if (sprites[0]->get_body().getPosition().x < 0)
  {
    sprites[0]->set_position(Vector2f(0, sprites[0]->get_body().getPosition().y));
  }
}



void World::collision_check()
{
  for (size_t i=0; i < sprites.size(); i++)
  {
    for (size_t k=i+1; k < sprites.size(); k++)
    {
      if (sprites[i]->get_body().getGlobalBounds().intersects(sprites[k]->get_body().getGlobalBounds()))
      {
        sprites[k]->collide(sprites[i]);
        sprites[i]->collide(sprites[k]);
      }
    }
  }
}



void World::spawn_objects()
{
  /* Skjuta */
  if (sprites[0]->shoot())
  {
    sprites.push_back(std::move(std::unique_ptr<Friendly_Bullet>{new Friendly_Bullet(&bulletTex, sprites[0]->get_body().getPosition() + Vector2f(10,0))}));
  }
  for (size_t i=1; i < sprites.size(); i++)
  {
    if (sprites[i]->shoot())
    {
      sprites.push_back(std::move(std::unique_ptr<Enemy_Bullet>{new Enemy_Bullet(&bulletTex, sprites[i]->get_body().getPosition() + Vector2f(10,60))}));
    }
  }

  /* Fiende */
  if (enemySpawnTimer < 150)
  {
    enemySpawnTimer++;
  }
  if (enemySpawnTimer >= 150)
  {
    sprites.push_back(std::move(std::unique_ptr<Enemy>{new Enemy(&enemyTex, Vector2u(800,600))}));
    enemySpawnTimer = 0; /* reset */
  }

  /* Asteroid */
  if (asteroidSpawnTimer < 50)
  {
    asteroidSpawnTimer++;
  }
  if (asteroidSpawnTimer >= 50)
  {
    sprites.push_back(std::move(std::unique_ptr<Asteroid> {new Asteroid(&asteroidTex, Vector2u(800,600))}));
    asteroidSpawnTimer = 0; /* reset */
  }
}



void World::draw(RenderWindow& window)
{

  window.clear();
  window.draw(background);
  /* Sprites */
  for (size_t i=0; i < sprites.size(); i++)
  {
      window.draw(sprites[i]->get_body());
  }
  /* UI */
  window.draw(scoreText);
  window.display();
}



void World::pause_check()
{
}



void World::update_sprite_vector()
{
  /* ta bort förstörda objekt från vektorn */
  for (size_t i=1; i < sprites.size(); i++)
  {
    if (sprites[i]->is_destroyed())
    {
      update_score(i);
      remove_from_list(i);
    }
  }
}



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

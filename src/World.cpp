/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    World.cpp
 * Enhetsnamn: World
 * Typ:        Definitioner hörande till modul Frame, Objet och Pause
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil kollar vad för händelser som sker under spelet. Tex
 * ifall spelaren trycker på paus-knappen, sparar spelarens poäng till en fil,
 * byten mellan skärmarna från spel till paus och tillbaks. Spel till game over.
 * Kollar kollision mellan alla spelareskepp och objekten. Hanterar hur snabt
 * fiendeskepp och asteroider ska spawna. Hanterar poäng och skriver ut det
 * på skärmen och sparar dessa i en text-fil.
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <iostream>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<string>
#include<sstream>
#include <fstream>
#include <utility>
#include"World.h"


using namespace sf;



/* %%%%%%%%%%%%%%%%%%%%%%%% Main %%%%%%%%%%%%%%%%%%%%%%%% */
World::World(Font& font)
  : score{0}, enemySpawnTimer{0}, asteroidSpawnTimer{0}
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


int World::Run(RenderWindow& window)
{
	Event Event;
	while (window.isOpen())
	{
		while (window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				return (-1);
			}
			if (Event.type == sf::Event::KeyPressed)
			{
				switch (Event.key.code)
				{
					case sf::Keyboard::Escape:
					std::cout << "Pause" << std::endl;
					return 3;
					break;
				}
			}
		}
		if(sprites[0]->is_destroyed())
		{
			save();
			reset();
			return 4;
		}
		spawn_objects();
		move_sprites();
		collision_check();
		update_sprite_vector();
		draw(window);
	}
	return -1;
}



void World::reset()
{
	sprites.clear();
	sprites.push_back(std::move(std::unique_ptr<Player> {new Player(&playerTex)}));
	score = 0;
}



void World::save()
{
  std::ofstream writeFile;
	writeFile.open("gamedata/scores.txt");
  if (writeFile.is_open())
  {
    if (score > highscore4)
    {
        highscore4 = score;
    }
    if (score > highscore3)
    {
			highscore4 = highscore3;
      highscore3 = score;
    }
		if (score > highscore2)
    {
			highscore3 = highscore2;
      highscore2 = score;
    }
		if (score > highscore1)
    {
			highscore2 = highscore1;
      highscore1 = score;
    }
		if (score > highscore0)
    {
			highscore1 = highscore0;
      highscore0 = score;
    }
    writeFile << highscore0 << std::endl;
    writeFile << highscore1 << std::endl;
    writeFile << highscore2 << std::endl;
    writeFile << highscore3 << std::endl;
    writeFile << highscore4 << std::endl;
		writeFile << score << std::endl;
  }
  writeFile.close();
}


/*
 * SLUT PÅ FILEN World.cpp
 */

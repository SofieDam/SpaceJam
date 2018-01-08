/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    World.h
 * Enhetsnamn: World
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul sköter spelskärmen.
 *
 */

#ifndef WORLD_H
#define WORLD_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<sstream>
#include<vector>
#include <memory>
#include "Frame.h"
#include "Pause.h"
#include "Object.h"


class World : public Frame
{
public:

  World(sf::Font& font);
  ~World() {};

  void remove_from_list(long unsigned& m);
  void collision_check();
  void move_sprites();
  void update_score(int const i);
  void spawn_objects();
  void draw(sf::RenderWindow& window);
  void update_sprite_vector();
  int Run(sf::RenderWindow& window);
  void reset();

private:

  sf::Texture playerTex;;
  sf::Texture enemyTex;
  sf::Texture asteroidTex;
  sf::Texture bulletTex;
  sf::Texture backgroundTex;
  sf::Sprite background;

  int score;
  int enemySpawnTimer;
  int asteroidSpawnTimer;

  std::vector<std::unique_ptr<Object>> sprites;
  std::ostringstream ssScore;
  sf::Text scoreText;

  void save();
  int highscore0;
  int highscore1;
  int highscore2;
  int highscore3;
  int highscore4;
};


/*
 * SLUT PÅ FILEN World.h
 */
#endif

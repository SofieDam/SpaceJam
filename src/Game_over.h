/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Game_over.h
 * Enhetsnamn: Game_over
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul deklarerar funktionerna som behövs för Game Over-skärmen. Dessa är
 * poäng som tagits underspelets gång ska visas. De 5 högsta poängen ska visas.
 * Man ska kuna returnera till spelets Start meny. 
 *
 */

#ifndef GAME_OVER_H
#define GAME_OVER_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include<SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Frame.h"



class game_over : public Frame
{
public:
  game_over(sf::Font& font);
  ~game_over() {}
  int Run(sf::RenderWindow& window);

  Frame* start_menu_frame;

  void save(int score);
  void readFile();
  void printFile();

private:
  sf::Sprite background;
  sf::Texture game_overtex;
  sf::RectangleShape rectangle;

  int highscore0;
  int highscore1;
  int highscore2;
  int highscore3;
  int highscore4;
  int your_score;

  std::ostringstream ssScore;
  sf::Text scoreText;
  std::ostringstream yourssScore;
  sf::Text yourscoreText;
};

/*
 * SLUT PÅ FILEN Game_over.h
 */
#endif

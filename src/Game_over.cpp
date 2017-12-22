/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Game_over.cpp
 * Enhetsnamn: Game_over
 * Typ:        Definitioner hörande till modul Game_over
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil har tre huvudsaker. Först ska den visa spelarens
 * Score högst upp på vänster sida av Game Over-skärmen. Den ska skriva ut de 5 högsta
 * poängen som tagits under spelets gång. Dessa poäng skrivs ut med funktionen
 * printFile från en text-fil som har dessa poäng sparade. Och det sista är att
 * man ska kunna gå tillbaks till Start menyn. 
 */


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
#include "Game_over.h"

using namespace sf;



game_over::game_over(Font& font)
{
  if ( !game_overtex.loadFromFile("Sprites/game_over_background.png") )
  std::cout << "Error: Could not display game over background" << std::endl;

  game_overtex.setSmooth(true);
  background.scale(Vector2f(0.33f, 0.36f));
  background.setTexture(game_overtex);
  rectangle.setSize(Vector2f(194.9f, 45.9f));
  rectangle.setOutlineColor(Color(255,247,0,200));
  rectangle.setOutlineThickness(5);
  rectangle.setPosition(550, 500);
  rectangle.setFillColor(Color::Transparent);

  scoreText.setFont(font);
  scoreText.setString(ssScore.str());
  scoreText.setCharacterSize(30);
  scoreText.setColor(Color::Black);
  scoreText.setPosition(350.f, 350.f);

  yourscoreText.setFont(font);
  yourscoreText.setString(yourssScore.str());
  yourscoreText.setCharacterSize(30);
  yourscoreText.setColor(Color::Black);
  yourscoreText.setPosition(10.f, 10.f);
}



int game_over::Run(RenderWindow& window)
{
  readFile();
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
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
          return 0;
        }
      }
    }
    window.clear();
    window.draw(background);
    window.draw(rectangle);
    printFile();
    window.draw(scoreText);
    window.draw(yourscoreText);
    window.display();
  }
    return -1;
}



void game_over::readFile()
{
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
                 >> highscore4
                 >> your_score;
      }
  }
  readFile.close();
}




void game_over::printFile()
{
  ssScore.str("");
  ssScore << "1. " << highscore0 << "\n"
          << "2. " << highscore1 << "\n"
          << "3. " << highscore2 << "\n"
          << "4. " << highscore3 << "\n"
          << "5. " << highscore4;
  scoreText.setString(ssScore.str());

  yourssScore.str("");
  yourssScore << your_score;
  yourscoreText.setString(yourssScore.str());
}


/*
 * SLUT PÅ FILEN Game_over.h
 */

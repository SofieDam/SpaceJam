/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Scoreboard.cpp
 * Enhetsnamn: Scoreboard
 * Typ:        Definitioner hörande till modul Scoreboard
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil hanterar det 5 högsta poängen samt är ett av alternativen
 * när man kommer till startmenyn for att se Scoreboard. Läser av text-filen
 * som lagrar det fem högsta poängen. 
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Window.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Scoreboard.h"
#include "Frame.h"
#include "Start_menu.h"

using namespace sf;



scoreboard::scoreboard(RenderWindow* window, Font& font)
{
    window_x = window->getSize().x;
    window_y = window->getSize().y;
  if (!highscore_texture.loadFromFile("Sprites/scoreboard.png"))
  {
       std::cout << "Error could not load scoreboard!" << std::endl;
  }

  highscore_sprite.setTexture(highscore_texture);
  highscore_sprite.setPosition(window_x/4.5, window_y/7);
  highscore_sprite.scale(Vector2f(0.33f, 0.33f));

  scoreText.setFont(font);
  scoreText.setString(ssScore.str());
  scoreText.setCharacterSize(30);
  scoreText.setColor(Color::Black);
  scoreText.setPosition(350.f, 250.f);
}



void scoreboard::set_start_menu_frame(Frame* new_start_menu_frame)
{
  start_menu_frame = new_start_menu_frame;
}



int scoreboard::Run(RenderWindow& window)
{
  readFile();
  Event Event;
  while(window.isOpen())
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
    printFile();
    window.draw(highscore_sprite);
    window.draw(scoreText);
    window.display();
  }
  return -1;
}



void scoreboard::readFile()
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
                 >> highscore4;
      }
  }
  readFile.close();
}



void scoreboard::printFile()
{
  ssScore.str("");
  ssScore << "1. " << highscore0 << "\n"
          << "2. " << highscore1 << "\n"
          << "3. " << highscore2 << "\n"
          << "4. " << highscore3 << "\n"
          << "5. " << highscore4;
  scoreText.setString(ssScore.str());
}


/*
 * SLUT PÅ FILEN Scoreboard.cpp
 */

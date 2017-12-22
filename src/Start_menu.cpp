/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Start_menu.cpp
 * Enhetsnamn: Start_menu
 * Typ:        Definitioner hörande till modul Start_menu
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil sköter hela Startmenyn och hur man kommer vidare till antigen
 * Start Spel, Poängtavla eller Avsluta spel.  
 *
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include "SFML/Window.hpp"
#include "Start_menu.h"
#include "Frame.h"
#include "Object.h"

using namespace sf;



start_menu::start_menu(RenderWindow* window)
{
  window_x = window->getSize().x;
  window_y = window->getSize().y;

  if (!bgStartMenutex.loadFromFile("Sprites/start_menu_bg.png"))
  {
    std::cout << "Error could not load start_menu_bg!" << std::endl;
  }
  if (!PlayerImage.loadFromFile("Sprites/player (rot).png"))
  {
    std::cout << "Error could not load PlayerImage!" << std::endl;
  }

  bgStartMenutex.setSmooth(true);
  bgStartMenu.scale(Vector2f(0.33f, 0.36f));
  bgStartMenu.setTexture(bgStartMenutex);
  buttonCounter = 0;
  MAX_NUMBER_OF_BUTTON = 3;

  initDraw(window_x, window_y, &PlayerImage);
}



/* parametrized constructor */
void start_menu::initDraw(float width, float height, Texture *texture)
{
  this->SelectButton.setTexture(*texture);
  this->SelectButton.setScale(0.3f, 0.3f);
  this->SelectButton.setPosition(width/3.8, height/2.7);
}



void start_menu::MoveUp(float width, float height)
{
  if((buttonCounter - 1) >= 0)
  {
    --buttonCounter;
    this->SelectButton.setPosition(width/3.8, (height/2.7) + (80 * buttonCounter));
  }
}



void start_menu::MoveDown(float width, float height)
{
  if(buttonCounter + 1 < MAX_NUMBER_OF_BUTTON)
  {
    ++buttonCounter;
    SelectButton.setPosition(width/3.8, (height/2.7) + (80 * buttonCounter));
  }
}



int start_menu::get_buttonCounter()
{
  return buttonCounter;
}



int start_menu::Run(RenderWindow& window)
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
          case sf::Keyboard::Up:
          MoveUp(window_x, window_y);
          break;
          case sf::Keyboard::Down:
          MoveDown(window_x, window_y);
          break;
          case sf::Keyboard::Space:
          if(get_buttonCounter() == 0)
          {
            return 2;
          }
          else if(get_buttonCounter() == 1)
          {
            return 1;
          }
          else if(get_buttonCounter() == 2)
          {
            return -1;
          }
          break;
          default:
          break;
        }
      }
    }

        window.clear();
        window.draw(bgStartMenu);
        window.draw(SelectButton);
        window.display();
    }

   return -1;
}


/*
 * SLUT PÅ FILEN Start_menu.cpp
 */

/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Pause.cpp
 * Enhetsnamn: Pause
 * Typ:        Definitioner hörande till modul Pause
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil sköter spelets Paus-funktion när spelaren trycker på
 * Esc under speletsgång kommer spelet Pausas. För att ta sig vidare från pausmenyn har två knappsatser
 * implementerats med:
 * Alt. 1 Esc avsluta spelet -> Game Over menyn visas
 * Alt. 2 Space Fortsätta med spelet -> SPACEJAM!
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<iostream>
#include<utility>
#include"Pause.h"


using namespace sf;



Pause_Frame::Pause_Frame(Font& font)
{
  paused.setFont(font);
  paused.setCharacterSize(30);
  paused.setColor(Color::White);
  paused.setPosition(100.f, 100);
  paused.setString("                               GAME PAUSED\n         Press SPACE to CONTINUE or Esc to END GAME");
}



int Pause_Frame::Run(RenderWindow& window)
{
  Event Event;

  window.draw(paused);
  window.display();

  while (window.isOpen())
  {
    while (window.pollEvent(Event))
    {
      if (Event.type == sf::Event::KeyPressed)
      {
        switch (Event.key.code)
        {
          case sf::Keyboard::Space:
            return 2;
            break;
          case sf::Keyboard::Escape:
            return 4;
            break;
        }
      }
      if (Event.type == sf::Event::Closed)
      {
        return (-1);
      }
    }
    window.display();
  }

  return -1;
}

/*
 * SLUT PÅ FILEN Pause.cpp
 */

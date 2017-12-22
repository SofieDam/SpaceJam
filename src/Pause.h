/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Pause.h
 * Enhetsnamn: Pause
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul deklarerar spelfönstret Paus och alternativen som finns när man
 * pausat spelet. 
 */

#ifndef PAUSE_H
#define PAUSE_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Frame.h"
#include<iostream>



class Pause_Frame : public Frame
{
  public:
    Pause_Frame(sf::Font& font);
    ~Pause_Frame() {}

    int Run(sf::RenderWindow& window);

  private:
    sf::Text paused;
};


/*
 * SLUT PÅ FILEN Pause.h
 */
#endif

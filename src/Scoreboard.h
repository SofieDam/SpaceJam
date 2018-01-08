/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Scoreboard.h
 * Enhetsnamn: Scoreboard
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul deklarerar Scoreboard menyn, de fem högsta poängen och skriver ut
 * dessa.
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "SFML/Window.hpp"
#include "Frame.h"
#include "Start_menu.h"

using namespace sf;

class scoreboard : public Frame
{
  public:
    scoreboard(RenderWindow* Window, sf::Font& font);
    int Run(RenderWindow& window);
    void readFile();
    void printFile();
    void save();

  private:
    int highscore0;
    int highscore1;
    int highscore2;
    int highscore3;
    int highscore4;
    float window_x;
    float window_y;
    Sprite highscore_sprite;
    sf::Texture highscore_texture;
    std::ostringstream ssScore;
    sf::Text scoreText;
};

/*
 * SLUT PÅ FILEN Scoreboard.h
 */
#endif

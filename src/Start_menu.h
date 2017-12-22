/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Start_menu.h
 * Enhetsnamn: Start_menu
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul deklarerar hur startmenyn skrivs ut, hur många knappar det ska
 * finnas på startmenyn (tre st) och med vilka tangenter man ska kunna navigera sig
 * till de olika alternativen (Up-key och Down-key).
 *
 */

#ifndef START_MENU_H
#define START_MENU_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "Frame.h"
#include "Scoreboard.h"
#include "Object.h"

using namespace sf;



class start_menu : public Frame
{
  public:
    Sprite SelectButton;

    start_menu(RenderWindow* window);
    ~start_menu() {}

    /* Paramatiserad konstruktor */
    void initDraw(float width, float height, Texture *texture);
    void MoveUp(float width, float height);
    void MoveDown(float width, float height);
    int get_buttonCounter();
    int Run(sf::RenderWindow& window) override;

  private:
    int buttonCounter;
    int MAX_NUMBER_OF_BUTTON;
    sf::Sprite bgStartMenu;
    sf::Texture bgStartMenutex;
    sf::Texture PlayerImage;

    float window_x;
    float window_y;

};


/*
 * SLUT PÅ FILEN Frame.h
 */
#endif

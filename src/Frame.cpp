/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Frame.cpp
 * Enhetsnamn: Frame
 * Typ:        Definitioner hörande till modul Frame
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil sköter byterna mellan olika skärmar till spelet.
 * (Startmeny, poängtavla, spelskärm, pausskärm, och gameover-skärm)
 *
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"Frame.h"

using namespace sf;



/* -----------  The_Window  ----------- */

void The_Window::print_current_frame(RenderWindow& window)
{

}



void The_Window::change_current_frame(Frame* new_frame)
{
  Frame* tmp{new_frame};
  std::swap(tmp, current_frame);
}



void The_Window::set_current_frame(Frame* new_frame)
{
  Frame* tmp{new_frame};
  std::swap(tmp, current_frame);
}


/*
 * SLUT PÅ FILEN Framce.cpp
 */

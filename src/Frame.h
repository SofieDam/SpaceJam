/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Frame.h
 * Enhetsnamn: Frame
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul skapar deklarationer för att köra skärmarna samt skriva ut dessa och
 * byta mellan dessa skrämar i spelet SpaceJam. 
 */

#ifndef FRAME_H
#define FRAME_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<vector>
#include<utility>

class Frame
{
    public:
        virtual int Run(sf::RenderWindow& window)=0;
    protected:
};



class The_Window
{
    public:
        void change_current_frame(Frame* new_frame);
        void print_current_frame(sf::RenderWindow& window);
        void set_current_frame(Frame* new_frame);

    private:
        Frame* current_frame;
};


/*
 * SLUT PÅ FILEN Frame.h
 */
#endif

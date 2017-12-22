/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Main.cpp
 * Enhetsnamn: Main
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil är vår main fil som initierar allt i spelet SpaceJam.  
 *
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Frame.h"
#include "Start_menu.h"
#include "Scoreboard.h"
#include "Object.h"
#include "Pause.h"
#include "Game_over.h"



int main()
{
	std::vector<Frame*> Screens; 	/* Lista med alla screens */
	int screen = 0;								/* int som håller reda på vilken screen som ska köras */

	/* Window skapning */
	sf::RenderWindow App(sf::VideoMode(800, 600), "Space Jam", Style::Default);
	App.setFramerateLimit(60);

	/* ladda textstilen */
	Font font;
	font.loadFromFile("Font/Dosis-Light.ttf");

	App.setMouseCursorVisible(false);

	/* Skärm förberedelser */
	start_menu start_menu(&App);
	scoreboard scoreboard(&App, font);
	World World(font);
	Pause_Frame Pause_Frame(font);
	game_over game_over(font);

	Screens.push_back(&start_menu);
	Screens.push_back(&scoreboard);
	Screens.push_back(&World);
	Screens.push_back(&Pause_Frame);
	Screens.push_back(&game_over);

	while (screen >= 0)
	{
		screen = Screens[screen]->Run(App);
	}

	return 0;

}

/*
 * SLUT PÅ FILEN Main.cpp
 */

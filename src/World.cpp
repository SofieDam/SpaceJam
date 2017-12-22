/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    World.cpp
 * Enhetsnamn: World
 * Typ:        Definitioner hörande till modul Frame, Objet och Pause
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilashrami ,Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna implementeringsfil kollar vad för händelser som sker under spelet. Tex
 * ifall spelaren trycker på paus-knappen, sparar spelarens poäng till en fil,
 * byten mellan skärmarna från spel till paus och tillbaks. Spel till game over.   
 */


 /*
  * REFERERADE BIBLIOTEK OCH MODULER
  */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <iostream>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<string>
#include<sstream>
#include <fstream>
#include <utility>
#include"Frame.h"
#include "Object.h"
#include"Pause.h"

using namespace sf;



/* %%%%%%%%%%%%%%%%%%%%%%%% Main %%%%%%%%%%%%%%%%%%%%%%%% */

void World::Game()
{
}



int World::Run(RenderWindow& window)
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
					case sf::Keyboard::Escape:
					std::cout << "Pause" << std::endl;
					return 3;
					break;
				}
			}
		}
		if(sprites[0]->is_destroyed())
		{
			save();
			reset();
			return 4;
		}
		spawn_objects();
		move_sprites();
		collision_check();
		update_sprite_vector();
		draw(window);
	}
	return -1;
}



void World::set_pause_frame(Frame* new_pause_frame)
{
	pause_frame = new_pause_frame;
}



void World::set_game_over_frame(Frame* new_frame)
{
	game_over_frame = new_frame;
}



void World::unpause()
{
	game_paused = false;
}



void World::reset()
{
	sprites.clear();
	sprites.push_back(std::move(std::unique_ptr<Player> {new Player(&playerTex)}));
	score = 0;
}



void World::save()
{
  std::ofstream writeFile;
	writeFile.open("gamedata/scores.txt");
  if (writeFile.is_open())
  {
    if (score > highscore4)
    {
        highscore4 = score;
    }
    if (score > highscore3)
    {
			highscore4 = highscore3;
      highscore3 = score;
    }
		if (score > highscore2)
    {
			highscore3 = highscore2;
      highscore2 = score;
    }
		if (score > highscore1)
    {
			highscore2 = highscore1;
      highscore1 = score;
    }
		if (score > highscore0)
    {
			highscore1 = highscore0;
      highscore0 = score;
    }
    writeFile << highscore0 << std::endl;
    writeFile << highscore1 << std::endl;
    writeFile << highscore2 << std::endl;
    writeFile << highscore3 << std::endl;
    writeFile << highscore4 << std::endl;
		writeFile << score << std::endl;
  }
  writeFile.close();
}


/*
 * SLUT PÅ FILEN World.cpp
 */

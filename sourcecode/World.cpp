#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include <iostream>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<string>
#include<sstream>
#include"Player.h"
#include"Bullet.h"
#include"Enemy.h"


using namespace sf;

class Asteroid
{
public:
          Sprite rock;

          int Life;
          int LifeMax;

          Asteroid(Texture *texture, Vector2u windowSize)
          {
              this->LifeMax = 1;
              this->Life = this->LifeMax;
              this->rock.setTexture(*texture);
              this->rock.setScale(0.15f, 0.15f);
              this->rock.setPosition(rand()% (int)(windowSize.x  - this->rock.getGlobalBounds().width),
                                                        0.f - this->rock.getGlobalBounds().height);
          }

          ~Asteroid(){}

};


//%%%%%%%%%%%%%%%%%%%%%%%% Main %%%%%%%%%%%%%%%%%%%%%%%%
int main()
{
		srand(time(NULL));

    RenderWindow window(VideoMode(800,600), "SpaceJam", Style::Default);
    window.setFramerateLimit(60);

    //Text for gamescreen
    Font font;
    font.loadFromFile("Font/Dosis-Light.ttf");

    //Sprites from game (PLayer + Enemy + Bullet )
    Texture backgroundTex;
    backgroundTex.loadFromFile("Sprites/starbackg.png");
    Sprite background (backgroundTex);
    Texture playerTex;
    playerTex.loadFromFile("Sprites/player.png");
    Texture enemyTex;
    enemyTex.loadFromFile("Sprites/enemy.png");
    Texture asteroidTex;
    asteroidTex.loadFromFile("Sprites/asteroid.png");
    Texture bulletTex;
    bulletTex.loadFromFile("Sprites/bullet.png");

    //UI Text for Score
    int score = 0;
    std::ostringstream ssScore;
    ssScore << "Score: " << score;
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setString(ssScore.str());
    scoreText.setCharacterSize(20);
    scoreText.setColor(Color::White);
    scoreText.setPosition(10.f, 10.f);

    //Paused Game
    Text paused;
    paused.setFont(font);
    paused.setCharacterSize(50);
    paused.setColor(Color::White);
    paused.setPosition(250.f, 100);
    paused.setString("GAME PAUSED");

    //Only temporary to see if the collision worked
    Text gameovertxt;
    gameovertxt.setFont(font);
    gameovertxt.setCharacterSize(20);
    gameovertxt.setColor(Color::Red);
    gameovertxt.setPosition(300.f, window.getSize().y / 2);
    gameovertxt.setString("GAME OVER!");

    //Player
    Player player(&playerTex);
    int shootTimer = 20;

    //Enemy
    int enemySpawnTimer = 10;
    std::vector<Enemy> enemies;

    //Asteroid
    int asteroidSpawnTimer = 10;
    std::vector<Asteroid> rocks;

    bool pauseGame = false;
    //Main loop

    while (window.isOpen())
    {
          Event event;
          while (window.pollEvent(event))
          switch (event.type)
          {
              case sf::Event::KeyPressed:

                   if(Keyboard::isKeyPressed(Keyboard::Escape))
                   {
                     if(pauseGame == false)
                     {
                        pauseGame = true;
                        std::cout << "PAUSE" << std::endl;
                     }
                     else if(pauseGame == true)
                     {
                        pauseGame = false;
                        std::cout << "RESUME" << std::endl;
                     }
                   }
                   break;

              case sf::Event::Closed:
              window.close();
              break;
          }



          //%%%%%%%%%%%%%%%%%%%%%%%% Update %%%%%%%%%%%%%%%%%%%%%%%%
          //Update player

          if(pauseGame == false)
          {
		          if (Keyboard::isKeyPressed(Keyboard::Left))
    				          player.body.move(-6.f, 0.f);
    		      if (Keyboard::isKeyPressed(Keyboard::Right))
				              player.body.move(6.f, 0.f);

          //Collision with window (boundries for the ship)
          //Left window
          if (player.body.getPosition().x <= 0)
    		          player.body.setPosition(0.f, player.body.getPosition().y);
          //Right window
          if (player.body.getPosition().x >= window.getSize().x - player.body.getGlobalBounds().width)
    			       player.body.setPosition(window.getSize().x - player.body.getGlobalBounds().width, player.body.getPosition().y);

          //Update Controls
          if (shootTimer < 10)
                  shootTimer++;

          //Shoot controls
          if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 10)
          {
              player.bullets.push_back(Bullet(&bulletTex, player.body.getPosition()));
                  shootTimer = 0; //reset timer
          }


          // Bullets
          for (size_t i = 0; i < player.bullets.size(); i++)
          {
              player.bullets[i].bullet.move(0.f,-10.f);
              if (player.bullets[i].bullet.getPosition().y <= 0)
              {
                  player.bullets.erase(player.bullets.begin() + i);
                  break;
              }

              //Enemy collision
              for (size_t k = 0; k < enemies.size(); k++)
              {
                  if(player.bullets[i].bullet.getGlobalBounds().intersects(enemies[k].body.getGlobalBounds()))
                  {
                      if (enemies[k].Life >= 1)
                      {
                          score = score + 100;
                          ssScore.str("");
                          ssScore << "Score " << score;
                          scoreText.setString(ssScore.str());
                          enemies.erase(enemies.begin() + k);
                      }
                      else
                              enemies[i].Life--;    //Enemy take damage

                      player.bullets.erase(player.bullets.begin() + i);
                      break;
                  }
              }
              for (size_t k = 0; k < rocks.size(); k++)
              {
                  if(player.bullets[i].bullet.getGlobalBounds().intersects(rocks[k].rock.getGlobalBounds()))
                  {
                      if (rocks[k].Life >= 1)
                      {
                          score = score + 50;
                          ssScore.str("");
                          ssScore << "Score " << score;
                          scoreText.setString(ssScore.str());
                          rocks.erase(rocks.begin() + k);
                      }
                      else
                              rocks[i].Life--;    //Enemy take damage

                      player.bullets.erase(player.bullets.begin() + i);
                      break;
                  }
              }
          }

          //Enemy
          if (enemySpawnTimer < 200)
                  enemySpawnTimer++;

          //Enemy spawn
          if (enemySpawnTimer >= 200)
          {
              enemies.push_back(Enemy(&enemyTex, window.getSize()));
                  enemySpawnTimer = 0; //reset
          }

          for (size_t i=0; i < enemies.size(); i++)
          {
              enemies[i].body.move(0.f, 2.f);

              if (enemies[i].body.getPosition().y >  window.getSize().y)
              {
                  enemies.erase(enemies.begin() + i);
                  break;
              }

              if (enemies[i].body.getGlobalBounds().intersects(player.body.getGlobalBounds()))
              {
                  enemies.erase(enemies.begin() + i);
                  player.Life--; //Player take damage
                  break;
              }
          }

          //Asteroid
          if (asteroidSpawnTimer < 150)
                  asteroidSpawnTimer++;

          //Asteroid spawn
          if (asteroidSpawnTimer >= 150)
          {
              rocks.push_back(Asteroid(&asteroidTex, window.getSize()));
                  asteroidSpawnTimer = 0; //reset
          }

          for (size_t i=0; i < rocks.size(); i++)
          {
              rocks[i].rock.move(0.f, 2.f);

              if (rocks[i].rock.getPosition().y >  window.getSize().y)
              {
                  rocks.erase(rocks.begin() + i);
                  break;
              }

              if (rocks[i].rock.getGlobalBounds().intersects(player.body.getGlobalBounds()))
              {
                  rocks.erase(rocks.begin() + i);
                  player.Life--; //Player take damage
                  break;
              }
          }
          }


          // %%%%%%%%%%%%%%%%%%%%%%%% Draw %%%%%%%%%%%%%%%%%%%%%%%%
          window.clear();

          //Player
          window.draw(background);
          window.draw(player.body);

          //Bullets
          for (size_t i=0; i < player.bullets.size(); i++)
          {
              window.draw(player.bullets[i].bullet);
          }

          //Enemy
          for (size_t i=0; i < enemies.size(); i++)
          {
              window.draw(enemies[i].body);
          }

          //Asteroid
          for (size_t i=0; i < rocks.size(); i++)
          {
              window.draw(rocks[i].rock);
          }

          //UI
          window.draw(scoreText);
          if (pauseGame == true)
          window.draw(paused);
          if (player.Life <= 0)
          window.draw(gameovertxt);

          window.display();

    }

    return 0;

}

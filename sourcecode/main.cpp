#include <iostream>
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<math.h>
#include<cstdlib>
#include<vector>
#include<string>

using namespace sf;

class Bullet
{
  public:
          Sprite bullet;

          Bullet(Texture *texture, Vector2f pos)
          {
            this->bullet.setTexture(*texture);
            this->bullet.setScale(0.06f, 0.06f);
            this->bullet.setPosition(pos);
          }
          ~Bullet() {};
};

class Player
{
  public:
          Sprite body;
          Texture *texture;

          int Life;
          int LifeMax;

          std::vector<Bullet> bullets;

          Player(Texture *texture)
          {
            this->LifeMax = 1;
            this->Life = this->LifeMax;

            this->texture = texture;
            this->body.setTexture(*texture);
            this->body.setScale(0.2f, 0.2f);
          }

         ~Player() {}

};

class Enemy
{
  public:
          Sprite body;

          int Life;
          int LifeMax;

          Enemy(Texture *texture, Vector2u windowSize)
          {
            this->LifeMax = 1;
            this->Life = this->LifeMax;
            this->body.setTexture(*texture);
            this->body.setScale(0.35f, 0.35f);
            this->body.setPosition(windowSize.x - this->body.getGlobalBounds().width, rand()% (int)(windowSize.y - this->body.getGlobalBounds().height));

          }
          ~Enemy(){}
};

int main()
{
   srand(time(NULL));

   RenderWindow window(VideoMode(800,600), "SpaceJam", Style::Default);
   window.setFramerateLimit(60);

   //Text for game
   Font font;
   font.loadFromFile("Font/Dosis-Light.ttf");
   //Sprites from game (PLayer + Enemy + Bullet )
   Texture playerTex;
   playerTex.loadFromFile("Sprites/cat.png");
   Texture enemyTex;
   enemyTex.loadFromFile("Sprites/doge.png");
   Texture bulletTex;
   bulletTex.loadFromFile("Sprites/bullet.png");

   //UI Text
  //  Text scoreText;
  //  scoreText.setFont(font);
  //  scoreText.setCharacterSize(20);
  //  scoreText.setColor(Color::White);
  //  scoreText.setPosition(10.f, 10.f);

   //Player
   //int score = 0;
   Player player(&playerTex);
   int shootTimer = 20;

    //Enemy
    int enemySpawnTimer = 0;
    std::vector<Enemy> enemies;


    while (window.isOpen())
    {
      Event event;
      while (window.pollEvent(event))
      {
        if (event.type == Event::Closed)
        window.close();
      }

      //Update player
      if (Keyboard::isKeyPressed(Keyboard::Up))
        player.body.move(0.f,-10.f);
      if (Keyboard::isKeyPressed(Keyboard::Down))
        player.body.move(0.f, 10.f);


      //Collision with window. Top and bottom boundries
      if(player.body.getPosition().y <= 0)
        player.body.setPosition(player.body.getPosition().x, 0.f);
      if (player.body.getPosition().y >= window.getSize().y - player.body.getGlobalBounds().height)
        player.body.setPosition(player.body.getPosition().x, window.getSize().y - player.body.getGlobalBounds().height);

      //Update Controls
      if (shootTimer < 10)
        shootTimer++;

      if (Keyboard::isKeyPressed(Keyboard::Space) && shootTimer >= 10) //Shoot
      {
        player.bullets.push_back(Bullet(&bulletTex, player.body.getPosition()));
        shootTimer = 0; //reset timer
      }
      // if (shootTimer < 10)
      //   shootTimer++;
      //
      // if(Mouse::isButtonPressed(Mouse::Left) && shootTimer >= 10) //Shooting
      // {
      //   player.bullets.push_back(Bullet(&bulletTex, player.body.getPosition()));
      //   shootTimer = 0; //reset timer
      // }

    //Bullets
    for (size_t i = 0; i < player.bullets.size(); i++)
    {
        //Bullets movement and out of window bounds
        player.bullets[i].bullet.move(20.f,0.f);

        if (player.bullets[i].bullet.getPosition().x > window.getSize().x)
        {
          player.bullets.erase(player.bullets.begin() + i);
          break;
        }
        //Enemy collision
        for (size_t k = 0; k < enemies.size(); k++)
        {
          if(player.bullets[i].bullet.getGlobalBounds().intersects(enemies[k].body.getGlobalBounds()))
          {
            if (enemies[k].Life >= 0)
            {
            //score += enemies[k].LifeMax;
            enemies.erase(enemies.begin() + k);
            }
          else
          enemies[i].Life--;    //Enemy take damage
          player.bullets.erase(player.bullets.begin() + i);
          break;                //only break this for-loop and not all
          }
        }
    }

    //Enemy
    if (enemySpawnTimer < 25)
        enemySpawnTimer++;

    //Enemy spawn
    if (enemySpawnTimer >= 25)
    {
      enemies.push_back(Enemy(&enemyTex, window.getSize()));
      enemySpawnTimer = 0; //reset
    }

    for (size_t i=0; i < enemies.size(); i++)
    {
      enemies[i].body.move(-6.f, 0.f);

      if (enemies[i].body.getPosition().x <= 0 - enemies[i].body.getGlobalBounds().width)
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

    //UI Update
    // scoreText.setString("Score:" + std::to_string(score));

    // %%%%%%%%%%%%%%%%%%%%%%%% Draw %%%%%%%%%%%%%%%%%%%%%%%%

    window.clear();

    //Player
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

    //UI
    //window.draw(scoreText);

    window.display();

    }

      return 0;
}

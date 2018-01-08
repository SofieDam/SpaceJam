/*
 * TDDC76 Projekt Grupp 8 - SPACEJAM
 * HANDLEDARE: Viktor Olsson
 *
 * IDENTIFIERING
 *
 * Filnamn:    Object.h
 * Enhetsnamn: Object
 * Typ:        Moduldeklaration
 * Revision:   0.1
 * Skriven av: Sofie Dam, Jasmina Hebib, Kartick Kapilasrhami, Thomas Ngai och Victor Rönnblad
 *
 *
 * BESKRIVNING
 *
 * Denna modul skapar alla spelares, fiendeskepp och asteroiders storlek,
 * rörelsehastighet och deras rörelsegränser (utanför skärm), var det ska skapas,
 * deras liv tills det dör.
 *
 */

#ifndef OBJECT_H
#define OBJECT_H

/*
 * REFERERADE BIBLIOTEK OCH MODULER
 */
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include<sstream>
#include<vector>
#include <memory>



/* -----------Object-------------- */

class Object
{
public:
  Object()
    : destroyed{false}, val{0} {}
  virtual ~Object()=default;

  virtual void collide(std::unique_ptr<Object>& other)=0;
  virtual void move()=0;
  virtual bool shoot()=0;

  void destroy();
  bool is_destroyed();
  sf::Sprite get_body();
  int get_val();
  void set_val(int i);
  void set_position(sf::Vector2f pos);

protected:
  sf::Sprite body;
  bool destroyed;   /* Objektet förstördes eller ej */
  int val;          /* poängvärdet som ges när det förstörs */
};



class Friendly_Bullet : public Object
{
  public:
          Friendly_Bullet(sf::Texture *texture, sf::Vector2f pos)
          {
            body.setTexture(*texture);
            body.setScale(0.05f, 0.05f);
            body.setPosition(pos);
          }
          ~Friendly_Bullet() {};

          void collide(std::unique_ptr<Object>& other) override;
          void move() override;
          bool shoot() override;
};



class Player : public Object
{
  public:
          int HP;
          int Max_HP;
          int shoot_timer;

          Player(sf::Texture *texture)
            : HP{1}, Max_HP{5}, shoot_timer{10}
          {
            body.setTexture(*texture);
            body.setScale(0.35f, 0.35f);
            body.setPosition(400.f, 520.f);
          }

         ~Player() {}

         void collide(std::unique_ptr<Object>& other) override;
         void move() override;
         bool shoot() override;
};



class Obstacle : public Object
{
public:

    Obstacle() {}
    ~Obstacle() {}

    void collide(std::unique_ptr<Object>& other) override;
    void move() override;
    bool shoot() override;
};



class Enemy : public Obstacle
{
  public:
          Enemy(sf::Texture *texture, sf::Vector2u windowSize)
            : phase{0}, salvo_counter{0}, salvo_timer{100}, shoot_timer{15}, shot_counter{0}
          {
            val = 100;
            body.setTexture(*texture);
            body.setScale(0.35f, 0.35f);
            body.setPosition(rand()% (int)(windowSize.x  - this->body.getGlobalBounds().width),
                                                      0.f - this->body.getGlobalBounds().height);
          }
          ~Enemy(){}

          int phase; /* bestämmer hur den ska röra på sig/skjuta osv. */
          int salvo_counter;
          int salvo_timer;
          int shoot_timer;
          int shot_counter;
          void move() override;
          bool shoot();
};



class Asteroid : public Obstacle
{
public:
          Asteroid(sf::Texture *texture, sf::Vector2u windowSize)
          {
              val = 50;
              body.setTexture(*texture);
              body.setScale(0.2f, 0.2f);
              body.setPosition(rand()% (int)(windowSize.x  - this->body.getGlobalBounds().width),
                                                        0.f - this->body.getGlobalBounds().height);
          }
          ~Asteroid(){}

          void move() override;
};



class Enemy_Bullet : public Obstacle
{
  public:
          Enemy_Bullet(sf::Texture *texture, sf::Vector2f pos)
          {
            this->body.setTexture(*texture);
            this->body.setScale(0.05f, 0.05f);
            this->body.setPosition(pos);
          }
          ~Enemy_Bullet() {};

          void collide(std::unique_ptr<Object>& other) override;
          void move() override;
};



/*
 * SLUT PÅ FILEN Object.h
 */
#endif

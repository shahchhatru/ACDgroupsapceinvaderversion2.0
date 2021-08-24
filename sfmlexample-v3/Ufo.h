/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/
#ifndef UFO_H
#define UFO_H
#include"Bullet.h"
#include"Player.h"
#include <SFML/Graphics.hpp>

//This class is the enemy of our player.
class Ufo : public sf::Sprite
{
private:

    int id;//Every Ufo object has a unique id the first element created will have a id of 0 and similarly second of 1 and so on.
    int posx;//it stores x position of the object
    int posy;//it stores y position of the object
    int xsize;//it stores width of the Ufo object.
    int ysize;//it stores height of the Ufo object.

public:
    //public static member variables
    static int xarray[max_enemy]; // 10 random x position for our Ufo objects
    static int yarray[max_enemy];//10 random y position for our Ufo objects
    static int noobj;// it stores total no of object
    static int score;// it stores the score by counting no of times resetObj function called.

    //constructor of Ufo class
    //it is preetty similar to constructor of player class
    Ufo(sf::Texture& texture,int px,int py);
    virtual ~Ufo();

    int Getposx() { return posx; }//getter method for x position of Ufo object
    void Setposx(int val) { posx = val; }//setter method for y position of Ufo object.
    int Getposy() { return posy; }//getter method for x position
    void Setposy(int val) { posy = val; }//setter method for y position
    int getxsize();     //it returns width of Ufo object

    int getysize() ;    //it returns height of Ufo object.
    void move_down();   //it moves down the Ufo object.
    bool detect_collisions(Player &player); // it returns false when player and Ufo collide
    bool detect_collisions(Bullet &player);//it returns false when Ufo and bullet object collide
    //static member function
    static void rand_number(); //it generates array of random numbers which gets filled in xarray and yarray
    //non static member functions
    int getid();//returns the id of the object
    void resetobj();// it resets the position of object when called. It gets called whenever bullets collide with ufo or Ufo goes behind the screen.
};
#endif // UFO_H

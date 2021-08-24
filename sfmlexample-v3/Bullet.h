/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/
#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include "Player.h"

class Bullet : public sf::Sprite
{
    public:
        // it is a constructor
        Bullet(sf::Texture& atexture,int px,int py);
        // Default destructor
        virtual ~Bullet();

        //it returns the current value of posx
        int Getposx() { return posx; }
        //it sets new value to posx
        void Setposx(int val) { posx = val; }
        //it returns the current value of posy
        int Getposy() { return posy; }
        //it sets new value to posy
        void Setposy(int val) { posy = val; }

        int Getxsize();//it returns width of Bullet
        int Getysize();//returns the height of Bullet
        void moveup();
        bool getdestroy();
        void setdestroy( bool val){ destroy=val;}

    protected:

    private:
        int posx; //it stores x position of bullet
        int posy; //it stores y position of bullet
        int xsize;//it stores width of the bullet object
        int ysize; //it stores height of the bullet object
        bool destroy; //it stores whether the bullet will be destroyed (when true) or not(when false)
};

#endif // BULLET_H

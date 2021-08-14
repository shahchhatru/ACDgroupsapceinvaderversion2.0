#ifndef UFO_H
#define UFO_H
#include"Bullet.h"
#include"Player.h"
#include <SFML/Graphics.hpp>

class Ufo : public sf::Sprite
{
private:

    int id;
    int posx;
    int posy;
    int xsize;
    int ysize;

public:
    static int xarray[10];
    static int yarray[10];
    static int noobj;
    static int score;
    Ufo(sf::Texture& texture,int px,int py);
    virtual ~Ufo();
    int Getposx() { return posx; }
    void Setposx(int val) { posx = val; }
    int Getposy() { return posy; }
    void Setposy(int val) { posy = val; }
    int getxsize();

    int getysize() ;
    void move_down();
    bool detect_collisions(Player &player);
    bool detect_collisions(Bullet &player);
    static void rand_number();
    int getid();
    void resetobj();
};


#endif // UFO_H

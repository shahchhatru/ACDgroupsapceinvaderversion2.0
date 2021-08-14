#include "Bullet.h"
#include<SFML/Graphics.hpp>
#define window_width 1380
#define window_height 800
Bullet::Bullet(sf::Texture& texture,int px,int py)
{
    //ctor
    setTexture(texture);
    setColor(sf::Color(255,255,255,240));
    setScale(0.02,0.02);
    // posx=px;
    //Edited
    px=px-10;
    py=py+25;
    Setposx(px);
    // posy=py;
    Setposy(py);
    destroy=false;
    setPosition(px,py);
    xsize=Getxsize();
    ysize=Getysize();

}

Bullet::~Bullet()
{
    //dtor
}

Bullet::Getxsize()
{
    int a;
    a=getTexture()->getSize().x *getScale().x;
    return a;
}

Bullet::Getysize()
{
    int a;
    a=getTexture()->getSize().y *getScale().y;
    return a;
}

void Bullet::moveup()
{
    if(posy>-10)
    {
        posy--;
    }
    else
    {
        destroy=true;
    }
    setPosition(posx,posy);
}

bool Bullet::getdestroy()
{
    return destroy;
}

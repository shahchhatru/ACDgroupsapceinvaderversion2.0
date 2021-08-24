/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/
#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture,int px,int py)
{
    //ctor
    setTexture(texture);
    setColor(sf::Color(255,255,255,240));
    setScale(0.02,0.02);
    px=px-10;
    py=py+25;
    Setposx(px);
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
    a=getTexture()->getSize().x *getScale().x;//it gives width of bullet
    return a;
}

Bullet::Getysize()
{
    int a;
    a=getTexture()->getSize().y *getScale().y;//it gives height of bullet
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

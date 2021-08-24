/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/
#include "Ufo.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

Ufo::Ufo(sf::Texture& texture,int px,int py)
{
    //ctor
    setTexture(texture);
    setColor(sf::Color(255,255,255,240));
    setScale(0.05,0.05);
    posx=px;
    posy=py;
    setPosition(px,py);
    xsize=getxsize();
    ysize=getysize();
    id=noobj;
    noobj++;
}
//static variables declaration;
int Ufo::noobj=0;
int Ufo::xarray[]={0};
int Ufo::yarray[]={0};
int Ufo::score=0;

Ufo::~Ufo()
{
    //dtor

}

Ufo::getxsize()
{
    int a;
    a=getTexture()->getSize().x *getScale().x;//it gives length or width of ufo
    return a;
}

Ufo::getysize()
{
    int a;
    a=getTexture()->getSize().y *getScale().y;//it gives height of ufo
    return a;
}

void Ufo::move_down()
{
    if(posy>win_height)
    {
        resetobj();
    }
    posy++;
    setPosition(posx,posy);
}

bool Ufo::detect_collisions(Player& player)
{

    int px,py;
    int ew,eh,pw,ph;//enemy and player width  height ;
    int emx=posx;
    int emy=posy;
    ew=getxsize();
    eh=getysize();
    px=player.Getposx();//x position of player
    py=player.Getposy();//y position of player
    pw=player.getxsize();
    ph=player.getysize();
    if(px<=emx && px+pw>=emx)
    {
        if(py>emy && py<emy+eh)
        {
            return false;
        }
        else if(py<=emy && py+ph>=emy)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if(px>=emx && px<=emx+ew)
    {
        if(py>=emy && py<=emy+eh)
        {
            return false;
        }
        else if(py<=emy && py+ph>=emy)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return true;

}

void Ufo::rand_number()
{
    srand(time(NULL));
    for(int i=0;i<max_enemy;i++)
    {
        xarray[i]=rand()%(win_width-49);
        yarray[i]=(rand()%200)*(-1);
    }
}

bool Ufo::detect_collisions(Bullet& player)
{

    int px,py;
    int ew,eh,pw,ph;//enemy and player width  height ;
    int emx=posx;
    int emy=posy;
    ew=getxsize();
    eh=getysize();
    px=player.Getposx();//x position of player
    py=player.Getposy();//y position of player
    pw=player.Getxsize();
    ph=player.Getysize();
    if(px<=emx && px+pw>=emx)
    {
        if(py>emy && py<emy+eh)
        {
            return false;
        }
        else if(py<=emy && py+ph>=emy)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if(px>=emx && px<=emx+ew)
    {
        if(py>=emy && py<=emy+eh)
        {
            return false;
        }
        else if(py<=emy && py+ph>=emy)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    return true;

}

void Ufo::resetobj()
{
    rand_number();
    score++;
    posx=xarray[id];
    posy=yarray[id];
}

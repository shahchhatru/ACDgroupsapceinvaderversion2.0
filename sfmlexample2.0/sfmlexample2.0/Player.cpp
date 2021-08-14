#include "Player.h"
#include<iostream>
#include<SFML/Graphics.hpp>

#define window_width 1380
#define window_height 800
Player::Player(sf::Texture& texture,int px,int py)
{

    setTexture(texture);
    setColor(sf::Color(255,255,255,240));
    setScale(0.1,0.1);
    posx=px;
    posy=py;
    setPosition(px,py);
    xsize=getxsize();
    ysize=getysize();

}

Player::getxsize()
{
    int a;
    a=getTexture()->getSize().x *getScale().x;
    return a;
}

Player::getysize()
{
    int  a;
    a=getTexture()->getSize().y *getScale().y;
    return a;
}

Player::~Player()
{
    //dtor
}

void Player::move_left()
{
    if(posx>0)
    {
        posx=posx-10;
        setPosition(posx,posy);
    }
}
void Player::move_right()
{
    if(posx<window_width-50)
    {
        posx=posx+10;
        setPosition(posx,posy);
    }
}

void Player::movex(int px)
{
    if(px<window_width-60)
    {
         posx=px;
    }
    setPosition(posx,posy);
}

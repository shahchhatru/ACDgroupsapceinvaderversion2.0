/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/
#include "Player.h"
#include<iostream>

Player::Player(sf::Texture& texture,int px,int py)
{
    //ctor
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
    a=getTexture()->getSize().x *getScale().x;//it gives width or length of player
    return a;
}

Player::getysize()
{
    int  a;
    a=getTexture()->getSize().y *getScale().y;//it gives height of player
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
    if(posx<win_width-50)
    {
        posx=posx+10;
        setPosition(posx,posy);
    }
}

void Player::movex(int px)
{
    if(px<win_width-60)
    {
         posx=px;
    }
    setPosition(posx,posy);
}

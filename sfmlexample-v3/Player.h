#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#define win_width 1380
#define win_height 800
#define max_enemy 30
class Player : public sf::Sprite
{
private:

    int posx;// x position of player
    int posy;// y position of player
    int xsize;// width of the player
    int ysize;// height of the player

public:

    Player(sf::Texture& texture,int px,int py);//it's a constructor it initializes a player object
    virtual ~Player();// it's a virtual distructor

    int Getposy() { return posy; }// it returns the x position of player
    int Getposx(){return posx;}// it returns the y position of player
    void Setposx(int val){posx=val;}// it sets the x position of player
    void Setposy(int val) { posy = val; }// it sets the y position of player
    int getxsize();// it calculates and returns the width of player.
    int getysize(); //it calculates and returns the height of player.
    void move_left();//it moves the player to the left
    void move_right();// it moves the player to the right
    void movex(int px);//it moves the player to the required x position.


};
#endif // PLAYER_H

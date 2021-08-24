/**
    Authors:
    076bct021 Chhatra Bikram Shah
    076bct013 Ayush Parajuli
    076bct023 Dhiraj Acharya
**/

#include <SFML/Graphics.hpp>
#include<iomanip>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<string>
#include<fstream>
#include<set>
#include<iterator>
#include<conio.h>
#include<sstream>
//user defined classes
#include"Player.h"
#include"Ufo.h"
#include"Bullet.h"
//some global variable that we will need our game
bool run=true;
#define win_width 1380
#define win_height 800
#define max_enemy 30
std::stringstream ss;
sf::RenderWindow window(sf::VideoMode(win_width, win_height), "Space invader  game!!");
std::vector<Ufo*> aliens;//a vector containing address of Ufo objects.
std::vector<Bullet*> bulets;//a vector containing address of Bullet objects.

//state class defination
//it is the class which controls all major events of the game like updating characters.
class State
{
private:

    Player* player;
    sf::Texture *enemyTexture;
    Ufo *e;
    Bullet *b;
    sf::Texture *bultexture;
    std::vector<Bullet*>::iterator itr;
    sf::Text text;
    sf::Text tex1;
    int score;
    int hscore;

public:

//constructor of State class
//it takes address of player object,address of Ufo texture address of bultext , font argument by reference.
State(Player* player1,sf::Texture* emtext,sf::Texture* bultext,sf::Font& font)
{

    player= player1;
    enemyTexture=emtext;
    bultexture=bultext;
    text.setFont(font);
    tex1.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Green);
    tex1.setFillColor(sf::Color::Blue);
    text.setPosition(win_width/2,600);

}
//it creates ufo object and stores it in vector<Ufo*> aliens;
void create_enemies()
{

    int j=aliens.size();
    if(j==0)
    {
        srand(time(NULL));
        for(int i=0;i<max_enemy;i++)
        {

            int x=rand()%win_width-50+1;
            int y=(rand()%800)*-1;
            e=new Ufo(*enemyTexture,x,y);
            aliens.push_back(e);

        }

    }

}
void shoot_bullet()
{

    int x=player->Getposx();
    int y=player->Getposy();
    int xs=player->getxsize();
    int ys=player->getysize();
    x=x+xs/2;
    y=y-ys/2;
    b=new Bullet(*bultexture,x,y);
    bulets.push_back(b);

}

// it updates character and returns the value of detects collision with player if player collides with enemy .
// else it returns true which sets the run to true and game loop continues
// this member function is responsible for detecting collision between bullet and Ufo .
// setting the value of bullet.destroy to true if collision happens and reseting the position of Ufo on bullet strike.
// it then iterates through the vector<*bullet> and checks for every element if it's destroy is set to true if true then it
// destroys the element and object at that address.
// it also updates ufo position every time moves them down and detect collision between the ufo and player and enemy and if
// collision detected then it returns false else it returns true.
bool update_character( )
{

    int s=bulets.size();
    for(int j=0;j<s;j++)
    {

        b=bulets.at(j);
        bulets.at(j)->moveup();
        window.draw(*bulets.at(j));
        bool detr;
        for(int i=0;i<max_enemy;i++)
        {

            e=aliens.at(i);
            detr=e->detect_collisions(*b);
            if(!detr)
            {

                e->resetobj();
                b->setdestroy(!detr);

            }

        }

    }
    itr=bulets.begin();
    bool destr;
    int j=0;
    while(itr!=bulets.end())
    {

       destr=bulets[j]->getdestroy();
       if(destr==true)
       {

           b=bulets[j];
           delete b;
           bulets.erase(itr);
           j--;
           itr--;

       }
       j++;
       itr++;

    }
    for(int i=0;i<max_enemy;i++)
    {

        run=aliens.at(i)->detect_collisions(*player);
        (*aliens.at(i)).move_down();
        window.draw(*aliens.at(i));
        if(run==false)
        {
            return run;
        }

    }
    return true;

}

//As the name suggest it displays score in the game screen.
void displayscore()
{

    ss.str("");
    ss<<Ufo::score;
    text.setString(ss.str());
    window.draw(text);

}

//it displays the play again screen once the player collides with Ufo.
void displayPlayAgain(bool& run)
{

    for(int i=0;i<max_enemy;i++)
        {
            e=aliens.at(i);
            delete e;
        }
    aliens.clear();
    window.clear(sf::Color::Black);
    text.setCharacterSize(35);
    text.setString("Press Q to quit OR r to restart");
    text.setPosition(400,400);
    ss.str(" ");
    ss<<"Your score is";
    ss<<std::setw(3)<<score;
    tex1.setString(ss.str());
    if(score>=hscore)
    {

        ss.str(" ");
        ss<<"NEW HIGH SCORE"<<std::setw(8)<<score;
        tex1.setString(ss.str());

    }
    tex1.setCharacterSize(60);
    tex1.setPosition(400,200);

    bool runn=true;
    sf::Event event;
    while(runn)
    {

        window.clear();
        window.draw(text);
        window.draw(tex1);
        window.display();

        while(window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type==sf::Event::KeyPressed)
            {

                if(event.key.code==sf::Keyboard::Q)
                {
                    window.close();
                    runn=false;
                    break;
                }
                else if(event.key.code==sf::Keyboard::R)
                {
                    run=true;
                    runn=false;
                    Ufo::noobj=0;
                    //text.setPosition(400,600);
                    //edited
                    text.setPosition(win_width/2,600);
                    text.setCharacterSize(50);
                    Ufo::score=0;
                    break;
                }

            }

        }

    }

}

// it basically reads a file and insert all the values from that file into a set and checks if
// the values are greater or not to the current score.
// if the current score is greater than the greatest value in set or equal to it
// then it display new Highscore is
// else it displays your highscore.
// it also sets the hscore value to highest score in game
void check_highscore()
{
    std::set<int,std::greater<int>> s1;
    int number;
    score=Ufo::score;
    std::ofstream fout;
    fout.open("numbers.txt",std::ios::app);
    fout<<Ufo::score<<std::endl;
    fout.close();
    std::ifstream fin;
    fin.open("numbers.txt");
    while(fin>>number)
    {
        s1.insert(number);
    }
    fin.close();
    fout.open("numbers.txt");
    std::set<int, std::greater<int> >::iterator itr;
    for (itr = s1.begin(); itr != s1.end(); itr++)
    {
        fout<<*itr<<std::endl;
    }
    fout.close();
    itr=s1.begin();
    hscore=*itr;
    if(Ufo::score==*itr)
    {
        std::cout<<"NEW HIGH SCORE IS "<<score<<std::endl;
    }else
    {
        std::cout<<"your score is "<<score<<std::endl;
        std::cout<<"HIGH SCORE IS "<<*itr<<std::endl;
    }

}

//it is the destructor of our State class
//it's releasing all the memory it occupied
~State()
{
    delete player;
    delete b;
    delete e;
    delete enemyTexture;
    delete bultexture;
}
};

int main()
{

   aliens.reserve(max_enemy);
   bulets.reserve(max_enemy);
   //loading texture;
   sf::Texture texture;
   sf::Texture texture1;
   sf::Texture texture2;
   try
   {
        if(!texture.loadFromFile("./images/ufo1.png"))
        {
            throw 1;
        }
        if(!texture1.loadFromFile("./images/player.png"))
        {
            throw 'a';
        }
        if(!texture2.loadFromFile("./images/fireball.png"))
        {
            throw "a";
        }
    }
    catch(int)
    {
        std::cout<<"coudnot load Ufo image:please specify correct path"<<std::endl;
    }
    catch(char)
    {
        std::cout<<"couldnot load Player image:please specify correct path"<<std::endl;
    }
    catch(const char*)
    {
        std::cout<<"couldnot load bullet images:please specify correct path"<<std::endl;
    }
   //loading fonts
    sf::Font font;
    try
    {
        if(!font.loadFromFile("./font/04b_19.ttf"))
        {
            throw 3;
        }
    }
    catch(int)
    {
        std::cout<<"unable to load the font file please specify correct path"<<std::endl;
    }

    Player player(texture1,100,600);
    State state(&player,&texture,&texture2,font);
    //extra loop for play again screen
    while(run)
    {
        run=true;
        //it creates our enemies i.e Ufo
        state.create_enemies();
        //game loop begins
        while (window.isOpen()&&run)
        {
            sf::Event event;//event object
            //while loops checks for every event of event object.
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();// it closes the game screen
                if(event.type==sf::Event::KeyPressed)
                {
                    if(event.key.code==sf::Keyboard::Left)
                    {
                        player.move_left();//player moves left
                    }
                    else if(event.key.code==sf::Keyboard::Right)
                    {
                        player.move_right();//player moves right
                    }
                    else if(event.key.code==sf::Keyboard::Space)
                    {
                    state.shoot_bullet();//it shoots bullet
                    }
                }
                if(event.type==sf::Event::MouseButtonPressed)
                {
                    //state.shoot_bullet();
                    state.shoot_bullet();//shoot bullet
                }
                if(event.type==sf::Event::MouseMoved)
                {
                    int mx=event.mouseMove.x;
                    player.movex(mx);//it moves player to required x position
                }
            }
            //updates characters and checks for collision
            run= state.update_character();
            window.draw(player);//draws player
            state.displayscore();//display score
            window.display();//displays everything drawn to screen.
            window.setFramerateLimit(200);//sets frame limit to 200
            window.clear(sf::Color::Black);//window clears with black color on every loop

        }

        state.check_highscore();
        state.displayPlayAgain(run);}
        return 0;
}

/*
int main()
{
   aliens.reserve(max_enemy);
   bulets.reserve(max_enemy);
   sf::Texture texture;
   if(!texture.loadFromFile("./images/ufo1.png"))
    {
        std::cout<<"load failed"<<std::endl;
    }
    sf::Texture texture1;
    if(!texture1.loadFromFile("./images/player.png"))
    {
        std::cout<<"load failed"<<std::endl;
    }
    sf::Texture texture2;
    if(!texture2.loadFromFile("./images/fireball.png"))
    {
        std::cout<<"load failed"<<std::endl;
    }
    sf::Font font;
    if(!font.loadFromFile("./font/04b_19.ttf"))
    {
        std::cout<<"unable to load the file"<<std::endl;
    }
    Player player(texture1,100,600);
    State state(&player,&texture,&texture2,font);

    while(run)
    {
        run=true;
        state.create_enemies();
        while (window.isOpen()&&run)
        {

            sf::Event event;
            while (window.pollEvent(event))
            {

                if (event.type == sf::Event::Closed)
                    window.close();
                if(event.type==sf::Event::KeyPressed)
                {

                    if(event.key.code==sf::Keyboard::Left)
                    {
                        player.move_left();
                    }
                    else if(event.key.code==sf::Keyboard::Right)
                    {
                        player.move_right();
                    }
                    else if(event.key.code==sf::Keyboard::Space)
                    {
                        state.shoot_bullet();
                    }

                }
                if(event.type==sf::Event::MouseButtonPressed)
                {
                    state.shoot_bullet();
                }
                if(event.type==sf::Event::MouseMoved)
                {
                    int mx=event.mouseMove.x;
                    player.movex(mx);
                }

            }
            run= state.update_character();
            window.draw(player);
            state.displayscore();
            window.display();
            window.setFramerateLimit(200);
            window.clear(sf::Color::Black);
        }
        state.check_highscore();
        state.displayPlayAgain(run);}
        getch();
        return 0;
}
*/

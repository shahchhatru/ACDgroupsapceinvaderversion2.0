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
#include"Player.h"
#include"Ufo.h"
#include"Bullet.h"

bool run=true;
int win_width=800;
int win_height=800;
std::stringstream ss;
sf::RenderWindow window(sf::VideoMode(win_width, win_height), "space invader  game!!");
 std::vector<Ufo*> aliens;
 std::vector<Bullet*> bulets;
class State{
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
    State(Player* player1,sf::Texture* emtext,sf::Texture* bultext,sf::Font& font){

        player= player1;
        enemyTexture=emtext;
        bultexture=bultext;
        text.setFont(font);
        tex1.setFont(font);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Green);
        tex1.setFillColor(sf::Color::Blue);
        text.setPosition(400,600);



    }

void create_enemies(){
   // aliens.reserve(10);

    int j=aliens.size();

if(j==0){
    srand(time(NULL));
    for(int i=0;i<10;i++){
        int x=rand()%win_width-50+1;
        int y=(rand()%800)*-1;
      // int y=0;
    e=new Ufo(*enemyTexture,x,y);

    aliens.push_back(e);

}
}
//return aliens;
}
void shoot_bullet(){
    int x=player->Getposx();
    int y=player->Getposy();
    int xs=player->getxsize();
    int ys=player->getysize();
    x=x+xs/2;
    y=y-ys/2;
    b=new Bullet(*bultexture,x,y);
    bulets.push_back(b);




}
bool update_character( ){
    int s=bulets.size();
   for(int j=0;j<s;j++){
        b=bulets.at(j);
        bulets.at(j)->moveup();
        window.draw(*bulets.at(j));
        bool detr;
        for(int i=0;i<10;i++){
            e=aliens.at(i);

            detr=e->detect_collisions(*b);
            if(!detr){
                    e->resetobj();
                b->setdestroy(!detr);
            }
        }
    }
    itr=bulets.begin();
    bool destr;
    int j=0;
    while(itr!=bulets.end()){
       destr=bulets[j]->getdestroy();
       if(destr==true){
        b=bulets[j];
        delete b;
        bulets.erase(itr);
        j--;
        itr--;
       }
       j++;
       itr++;
    }


for(int i=0;i<10;i++){


    //
    run=aliens.at(i)->detect_collisions(*player);
    (*aliens.at(i)).move_down();
    window.draw(*aliens.at(i));
    if(run==false){

        return run;
    }
   //if(run==false)return run;


}
return true;

}
void displayscore(){
        // text.setPosition(400,600);
        ss.str("");
        ss<<Ufo::score;
        text.setString(ss.str());
        window.draw(text);


}

void displayPlayAgain(bool& run){
    for(int i=0;i<10;i++){
                        e=aliens.at(i);
                        delete e;
                    }
                    aliens.clear();

    window.clear(sf::Color::Black);

    text.setCharacterSize(35);
    text.setString("Press Q to quit OR r to restart");
    text.setPosition(100,400);
    ss.str(" ");
    ss<<"Your score is  ";
    ss<<std::setw(5)<<score;
    //ss<<score;
    tex1.setString(ss.str());
    if(score>=hscore){
        ss.str(" ");
        ss<<"New HIgh score"<<std::setw(8)<<score;
        tex1.setString(ss.str());
    }
    tex1.setCharacterSize(60);
    tex1.setPosition(100,200);

    bool runn=true;
    sf::Event event;
    while(runn){
            window.clear();
        window.draw(text);
        window.draw(tex1);
        window.display();

    while(window.pollEvent(event)){


     if (event.type == sf::Event::Closed)
                window.close();

        if(event.type==sf::Event::KeyPressed)
        {
            if(event.key.code==sf::Keyboard::Q){
                    //player.move_left();
                    window.close();
                    runn=false;
                    break;

                }else if(event.key.code==sf::Keyboard::R){
               // player.move_right();
                    run=true;
                    runn=false;


                    Ufo::noobj=0;
                    text.setPosition(400,600);
                    Ufo::score=0;
                    break;

               }

        }
    }}

}
 void check_highscore(){
    std::set<int,std::greater<int>> s1;
    int number;
     score=Ufo::score;
    std::ofstream fout;
    fout.open("numbers.txt",std::ios::app);
    fout<<Ufo::score<<std::endl;
    fout.close();
    std::ifstream fin;
    fin.open("numbers.txt");
    while(fin>>number){
        s1.insert(number);
    }
    fin.close();
    //std::ofstream fout;
    fout.open("numbers.txt");
    std::set<int, std::greater<int> >::iterator itr;
      for (itr = s1.begin(); itr != s1.end(); itr++)
    {

        fout<<*itr<<std::endl;
    }

    fout.close();
    itr=s1.begin();
    hscore=*itr;
    if(Ufo::score==*itr){
        std::cout<<"new high score is  0"<<score<<std::endl;
    } else{
        std::cout<<"your score is"<<score<<std::endl;
        std::cout<<"HIGH SCORE IS "<<*itr<<std::endl;
    }


 }

 ~State(){
    delete player;
    delete b;
    delete e;
    delete enemyTexture;
    delete bultexture;
 }
};

int main()
{

   // sf::CircleShape shape(100.f);
   //declare our first player declare
   aliens.reserve(10);
   bulets.reserve(10);
   //loading texture;
   sf::Texture texture;
   if(!texture.loadFromFile("./images/ufo1.png")){
    std::cout<<"load failed"<<std::endl;
   }

    sf::Texture texture1;
    if(!texture1.loadFromFile("./images/player.png")){
    std::cout<<"load failed"<<std::endl;
   }
    sf::Texture texture2;
    if(!texture2.loadFromFile("./images/fireball.png")){
    std::cout<<"load failed"<<std::endl;
   }
   //loading fonts
    sf::Font font;
    if(!font.loadFromFile("./font/04b_19.ttf")){
        std::cout<<"unable to load the file"<<std::endl;
    }

    //sound buffer



    Player player(texture1,100,600);
    // State state(&window,&player,&texture);
    State state(&player,&texture,&texture2,font);

    while(run){
            run=true;
            //text.setPosition()
            state.create_enemies();
    while (window.isOpen()&&run)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
             if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Left){
                    player.move_left();
                }else if(event.key.code==sf::Keyboard::Right){
                player.move_right();}
                else if(event.key.code==sf::Keyboard::Space){
                    state.shoot_bullet();
                }

    }
      if(event.type==sf::Event::MouseButtonPressed){
                    //state.shoot_bullet();
                    state.shoot_bullet();


                }
    if(event.type==sf::Event::MouseMoved){

            int mx=event.mouseMove.x;
            player.movex(mx);


    }
}
        //spider.move_down();
        run= state.update_character();
        //window.draw(spider);
        window.draw(player);
        state.displayscore();
        window.display();
    window.setFramerateLimit(200);
        window.clear(sf::Color::Black);


        //window.draw(shape);

    }
   // window.close();
   state.check_highscore();
   state.displayPlayAgain(run);}
    getch();

    return 0;
}

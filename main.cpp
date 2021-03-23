#include<iostream>
#include"SFML/Graphics.hpp"
#include"SFML/System.hpp"
#include"SFML/Window.hpp"
#include"SFML/Audio.hpp"
#include<stdlib.h>
#include<vector>
#include<math.h>
#include<time.h>
#include<sstream>
using namespace sf;
using namespace std;
class Bullet
{
public:
	CircleShape bullet;
	Vector2f curvel;
	float maxspeed;

	Bullet(float radius = 2.f)
		: curvel(0.f, 0.f), maxspeed(15.f)
	{
		this->bullet.setRadius(radius);
		this->bullet.setFillColor(Color::Red);
	}
};




int main()
{
    srand(time(nullptr));
    //Thread thread(&play);
    RenderWindow menu(VideoMode(1280,720),"Menu",Style::Default);
    RenderWindow window(VideoMode(1280,720),"Trial");
    window.setActive(0);
    window.setVisible(0);
window.setFramerateLimit(45);
menu.setFramerateLimit(45);
    //bullets
  Bullet b1;
  vector<Bullet> bullets;

    	//Vectors
        Vector2f playerCenter;
        Vector2f mousePosWindow;
        Vector2f aimDir;
        Vector2f aimDirNorm;
        //crosshair
        CircleShape cross;
        cross.setRadius(5.f);
        cross.setOutlineThickness(2.f);
        cross.setOutlineColor(Color::Black);


    //Menu things
    Texture menuback,aboutback;
    Sprite mback,ab;
    Font menufont;
    Text tile,start,about,quit,goback,over,ended,score,scoretext;
    bool abclicked=0;
    bool waiting=0;
    //menu back
    menuback.loadFromFile("img/menuback.png");
    mback.setTexture(menuback);
    mback.setScale(Vector2f(0.68f,0.58f));
    //menu text
    menufont.loadFromFile("font/metal lord.ttf");
    //title
    tile.setFont(menufont);
    tile.setCharacterSize(100);
    tile.setColor(Color::White);
    tile.setString("DeathEater Penguin");
    tile.setPosition(Vector2f(150.f,100.f));
    //start
    start.setFont(menufont);
    start.setCharacterSize(40);
    start.setColor(Color::White);
    start.setString("Start");
    start.setPosition(Vector2f(180.f,350.f));
    //about
    aboutback.loadFromFile("img/about.png");
    ab.setTexture(aboutback);
    ab.setScale(Vector2f(0.68f,0.58f));
    about.setFont(menufont);
    about.setCharacterSize(40);
    about.setColor(Color::White);
    about.setString("About");
    about.setPosition(Vector2f(180.f,450.f));
    //exit
    quit.setFont(menufont);
    quit.setCharacterSize(40);
    quit.setColor(Color::White);
    quit.setString("Exit");
    quit.setPosition(Vector2f(180.f,550.f));
    //back
    goback.setFont(menufont);
    goback.setCharacterSize(40);
    goback.setColor(Color::Red);
    goback.setString("BACK");
    goback.setPosition(Vector2f(50.f,650.f));
///////Game over/////////////////
    over.setFont(menufont);
    over.setCharacterSize(100);
    over.setColor(Color::Black);
    over.setString("GAME OVER");
    over.setPosition(Vector2f(150.f,100.f));
     ended.setFont(menufont);
    ended.setCharacterSize(40);
    ended.setColor(Color::Red);
    ended.setString("PRESS ESC TO EXIT");
    ended.setPosition(Vector2f(50.f,650.f));
    bool game=0;


    //window.setVerticalSyncEnabled(1);
    Clock clock;
    float dt,multiplier;
    float vel=2.f,jumpvel=0,acc=0.5f,location=300;
   int onground=1;
    int jumphigh=30;


    //DECLARATIONS
    Texture walltext,backtext;
    Sprite backg,wall,backg2,wall2;

    //GROUND 1
    walltext.loadFromFile("img/ground.png");
    wall.setTexture(walltext);
    wall.setScale(Vector2f(1.245f,1.f));
    //FOREST 1
    backtext.loadFromFile("img/back.png");
    backg.setTexture(backtext);
    backg.setPosition(Vector2f(0.f,0.f));
    backg.setScale(Vector2f(3.33f,3.06f));
    //GROUND 2
    wall2.setTexture(walltext);
    wall2.setScale(Vector2f(1.245f,1.f));
    wall2.setPosition(Vector2f(backg.getPosition().x+1278,0.f));
    //FOREST 2
    backg2.setTexture(backtext);
    backg2.setPosition(Vector2f(backg.getPosition().x+1278,0.f));
    backg2.setScale(Vector2f(3.33f,3.06f));
    //PLAYER
    Texture playtextrun,shotr,shotur;
    Sprite sold2,shot1,shot3;
    int movecount=0;
    float initr[8],pr[8],inits[8],ps[8];
    //stand and run in right
    pr[2]=415; initr[2]=0;
    pr[3]=442; initr[3]=0;

    //shot in right
    ps[0]=615; inits[0]=0;
    ps[1]=442; inits[1]=0;

    // shot up right
    ps[4]=550; inits[4]=0;
    ps[5]=568; inits[5]=0;
    //enemy
    ps[6]=144; inits[6]=7;
    ps[7]=47; inits[7]=0;


    //running right
    playtextrun.loadFromFile("img/playerrunr.png");
    sold2.setTexture(playtextrun);
    sold2.setTextureRect(IntRect(initr[2]*pr[2],initr[3]*pr[3],pr[2],pr[3]));
    sold2.setScale(Vector2f(0.24f,0.226f));
    sold2.setPosition(Vector2f(300.f,420.f));

    // run shot right
    shotr.loadFromFile("img/runshotr.png");
    shot1.setTexture(shotr);
    shot1.setTextureRect(IntRect(inits[0]*ps[0],inits[1]*ps[1],ps[0],ps[1]));
    shot1.setScale(Vector2f(0.24f,0.226f));
    shot1.setPosition(Vector2f(sold2.getPosition().x,420.f));

    // run shot diag right
    shotur.loadFromFile("img/shotdr.png");
    shot3.setTexture(shotur);
    shot3.setTextureRect(IntRect(inits[4]*ps[4],inits[5]*ps[5],ps[4],ps[5]));
    shot3.setScale(Vector2f(0.24f,0.226f));
    shot3.setPosition(Vector2f(sold2.getPosition().x,390.f));

////Enemy////////////////////////////////////////////////////////////
	Texture enm,enm2;
	Sprite enemy,enemy2;
	enm.loadFromFile("img/enemy2.png");
	enemy.setTexture(enm);
	enemy.setScale(Vector2f(0.7f,0.7f));
	enemy.setPosition(Vector2f((rand()%681)+600,rand()%521));
	int spawnCounter = 20;

	std::vector<Sprite> enemies;


	//SCORE & Health bar
	float sc=0;
	stringstream s;
	 score.setFont(menufont);
    score.setCharacterSize(40);
    score.setColor(Color::Red);
    score.setPosition(Vector2f(150.f,0.f));
     scoretext.setFont(menufont);
    scoretext.setCharacterSize(40);
    scoretext.setColor(Color::Red);
    scoretext.setString("SCORE : ");
// SOUND
    SoundBuffer gamebuf;
    Sound gamesound;



        Music menusound;
    if(!menusound.openFromFile("menusound.wav"))
        cout<<"sound not open\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
menusound.play();
menusound.setLoop(true);
gamebuf.loadFromFile("sounds/gamesound.wav");
gamesound.setBuffer(gamebuf);
gamesound.setLoop(true);


    while(menu.isOpen())
    {//thread.launch();


        Event eventm;
        while(menu.pollEvent(eventm))
        {
           if(eventm.type==Event::Closed)
               {
                   menusound.stop();
                menu.close();
               }
                //thread.terminate();
        }

        if(Mouse::isButtonPressed(Mouse::Left))
        {
            Vector2f mousepos=menu.mapPixelToCoords(Mouse::getPosition(menu));
            //bounds
            FloatRect stbound=start.getGlobalBounds(),
                      abbound=about.getGlobalBounds(),
                      exbound=quit.getGlobalBounds(),
                      bcbound=goback.getGlobalBounds();

           if(abclicked==0)
            {
            if(stbound.contains(mousepos))
                {
                    menusound.stop();
                    //thread.terminate();
                    window.setActive(1);
                    window.setVisible(1);
                    menu.setActive(0);
                    menu.setVisible(0);
                    window.setMouseCursorVisible(0);
                    gamesound.play();

                    while(window.isOpen())
                    {
                        Event event;
                        while(window.pollEvent(event))
                        {
                            if(event.type==Event::Closed)
                                {

                                    gamesound.stop();
                                    menu.close();
                                    window.close();
                                    exit(0);

                                }
                            if(event.type==Event::KeyPressed && event.key.code==Keyboard::Escape)
                                {
                                   gamesound.stop();
                                   menu.close();
                                   window.close();
                                   exit(0);
                                }
                        }
        //Update
if(!waiting)
{

       dt=clock.restart().asSeconds();
       enemy.setPosition(Vector2f((rand()%681)+600,rand()%521));

        //vectors update
        if(movecount==6)
            playerCenter = Vector2f(shot3.getPosition().x+85,sold2.getPosition().y);
        else
            playerCenter = Vector2f(shot1.getPosition().x+85,shot1.getPosition().y+45);
        mousePosWindow = Vector2f(Mouse::getPosition(window));
        aimDir = mousePosWindow - playerCenter;
        aimDirNorm = Vector2f(aimDir.x/(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2))),aimDir.y/(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2))));
        cross.setPosition(mousePosWindow);
//right walk update/////////////////////////////////////////////////////////////////////////////////////////////////////

                        shot1.setPosition(Vector2f(sold2.getPosition().x,sold2.getPosition().y));
                        shot3.setPosition(Vector2f(sold2.getPosition().x,sold2.getPosition().y-25));
                      if(sold2.getPosition().x>=window.getSize().x )
                            sold2.setPosition(Vector2f(-100.f,420.f));
                        cout<<"1 sec passed"<<"\n";
                        ++initr[2];
                        cout<<"initx : "<<initr[2]<<"\n";
                        sold2.setTextureRect(IntRect(initr[2]*pr[2],initr[3]*pr[3],pr[2],pr[3]));

                        if(initr[2]>=5)
                        {
                            initr[2]=0;
                            ++initr[3];
                                if(initr[3]>=3)
                                    initr[3]=0;
                        }

                movecount=1;



//move right with shot//////////////////////////////////////////////////////////////////////////////////////
         if( Mouse::isButtonPressed(Mouse::Left))
            {//move upright with shot
                if((Mouse::isButtonPressed(Mouse::Left))&& (Mouse::getPosition(window).x>shot3.getPosition().x)&& (Mouse::getPosition(window).y<=400))
                {

                cout<<"1 sec passed"<<"\n";
                        ++inits[4];
                        cout<<"Diagonal right up initx : "<<inits[4]<<"\n";
                        shot3.setTextureRect(IntRect(inits[4]*ps[4],inits[5]*ps[5],ps[4],ps[5]));

                        if(inits[4]>4)
                        {
                            inits[4]=0;
                            ++inits[5];
                                if(inits[5]>=3)
                                    inits[5]=0;
                        }

                movecount=6;
                }

             else
             {
///////////run right with gun shot ///////////////////////////////////////////////////////////////////////
                       cout<<"1 sec passed"<<"\n";
                        ++inits[0];
                        cout<<"initx : "<<inits[0]<<"\n";
                        shot1.setTextureRect(IntRect(inits[0]*ps[0],inits[1]*ps[1],ps[0],ps[1]));

                        if(inits[0]>=5)
                        {
                            inits[0]=0;
                            ++inits[1];
                                if(inits[1]>=3)
                                    inits[1]=0;
                        }

                movecount=4;
             }
            }




//Enemies//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (spawnCounter < 10)
			spawnCounter++;

		if(spawnCounter >= 10 && enemies.size() < 50)
		{

			enemies.push_back(Sprite(enemy));

			spawnCounter = 0;
		}


		for (size_t i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(-2.5f,0.f);
		}



///////////SHOOTING////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (Mouse::isButtonPressed(Mouse::Left)&&(mousePosWindow.x>sold2.getPosition().x+150))
            {
                b1.bullet.setPosition(playerCenter);
                b1.curvel = aimDirNorm * b1.maxspeed;

                bullets.push_back(Bullet(b1));
            }

    for (size_t i = 0; i < bullets.size(); i++)
		{
			bullets[i].bullet.move(Vector2f(bullets[i].curvel.x,bullets[i].curvel.y));

			//Out of bounds
			if (bullets[i].bullet.getPosition().x > window.getSize().x
				|| bullets[i].bullet.getPosition().y < 0 || bullets[i].bullet.getPosition().y > window.getSize().y)
			{
				bullets.erase(bullets.begin() + i);

			}
			else
            {
                for (size_t k = 0; k < enemies.size(); k++)
				{
					if (bullets[i].bullet.getGlobalBounds().intersects(enemies[k].getGlobalBounds()) )
					{
						bullets.erase(bullets.begin() + i);
						enemies.erase(enemies.begin() + k);

						break;
					}

				}
            }
        }




 /////////////////LOSING CHECK /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
           for(size_t t=0;t<enemies.size();t++)
              {
                  if(enemies[t].getGlobalBounds().intersects(sold2.getGlobalBounds()) || enemies[t].getPosition().x<=0)
                  {
                     game=1;
                  }
              }


              //////////////////SCORE////////////////////////////

              sc+=0.1;




////////FOREST ANIMATION////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vel+=0.01;
   backg.move(-vel,0.f);
    backg2.move(-vel,0.f);
    if(backg.getPosition().x+1280<0)
        backg.setPosition(Vector2f(backg2.getPosition().x+1278,0.f));
    if(backg2.getPosition().x+1280<0)
        backg2.setPosition(Vector2f(backg.getPosition().x+1278,0.f));
//////////WALL ANIMATION/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    wall.move(-vel,0.f);
    wall2.move(-vel,0.f);
    if(wall.getPosition().x+1280<0)
        wall.setPosition(Vector2f(wall2.getPosition().x+1278,0.f));
    if(wall2.getPosition().x+1280<0)
        wall2.setPosition(Vector2f(wall.getPosition().x+1278,0.f));
}
        //Draw
        window.clear();
        //draw here

        window.draw(wall);
        window.draw(wall2);
        window.draw(backg);
        window.draw(backg2);
        window.draw(cross);






		for (size_t i = 0; i < enemies.size(); i++)
		{
		window.draw(enemies[i]);
        }



        if(movecount==1)
        {
            window.draw(sold2);
            for (size_t i = 0; i < bullets.size(); i++)
                {
                    window.draw(bullets[i].bullet);
                }

        }
        else if(movecount==4)
        {
            window.draw(shot1);
             for (size_t i = 0; i < bullets.size(); i++)
                {
                    window.draw(bullets[i].bullet);
                }
        }

        else if(movecount==6)
        {
            window.draw(shot3);
            for (size_t i = 0; i < bullets.size(); i++)
                {
                    window.draw(bullets[i].bullet);
                }

        }
             if(game==1)
        {
            window.draw(over);
            window.draw(ended);
             s<<sc;
            score.setString(s.str());
            s.str("");
            window.draw(scoretext);
            window.draw(score);
            gamesound.stop();

            waiting=1;

        }

        window.display();
    }//window ended

                }
            else if(abbound.contains(mousepos))
                {
                    abclicked=1;

                }
            else if(exbound.contains(mousepos))
                {
                    menu.close();
                }

            }
            else if(bcbound.contains(mousepos))
            {
                abclicked=0;
            }

        }
        menu.clear();
        if(abclicked==1)
        {
            menu.draw(ab);
            menu.draw(goback);
        }
        else if(abclicked==0)
        {
            menu.draw(mback);
            menu.draw(start);
            menu.draw(tile);
            menu.draw(about);
            menu.draw(quit);
        }

        menu.display();
    }
    return 0;
}



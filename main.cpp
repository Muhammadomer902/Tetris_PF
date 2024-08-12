/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */
#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
using namespace std;

int easy();
int hard();

void menu()
{
    Sprite background; // Game background sprite
    Texture bg_texture;
    Font font;
    bg_texture.loadFromFile("img/th.png");
    background.setTexture(bg_texture);
    background.setScale(2, 2);
    font.loadFromFile("chrusty-rock-font/ChrustyRock-ORLA.ttf");

    Text level1("EASY LEVEL", font, 50);
    level1.setPosition(80, 75);
    Text level2("HARD LEVEL", font, 50);
    level2.setPosition(80, 175);
    Text Quit("Exit Game", font, 50);
    Quit.setPosition(80, 275);

    RenderWindow window(sf::VideoMode(450, 420), title);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Vector2i mousePos = Mouse::getPosition(window);

                    // Check if the "EASY LEVEL" text is clicked
                    if (level1.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        window.close();
                        easy(); // Call easy level function
                    }
                    // Check if the "HARD LEVEL" text is clicked
                    if (level2.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        window.close();
                        hard(); // Call hard level function
                    }
                    // Check if the "Exit Game" text is clicked
                    if (Quit.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        window.close();
                    }
                }
            }
        }

        window.clear(Color::Black); // clears the screen
        window.draw(background);    // setting background
        window.draw(level1);
        window.draw(level2);
        window.draw(Quit);
        window.display(); // Displaying all the sprites
    }
}

int main()
{
    menu();
return 0;
}   
    
//<--for easy level-->//
    
int easy(){    
    srand(time(0));
    RenderWindow window(sf::VideoMode(450,420), title);
    Texture obj1, obj2, obj3, obj4;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/bomb.png");
    
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    Sprite sprite(obj1), background(obj2), frame(obj3), sprite1(obj4);
    int delta_x=0, colorNum=1, caser = 0, CELL_SIZE = 8, lineduring1fall = 0,score= 0;
    float timer=0, delay=0.3;
    bool rotate=0, linefull=0, space = 0, pause = 0;
    Clock clock;


    while (window.isOpen()){
           
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                   space = true;
                else if (e.key.code == Keyboard::H)
                   {
                    if(pause)
                     pause=false;
                    else
                     pause = true;
                   }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.07;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
            
        if (pause){
         continue;
         }
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        linefull = Gameover(M,N);
        if(linefull)
        break;
        fallingPiece(timer, delay, colorNum);               //Example: fallingPiece() function is called here
        movementofblocks(delta_x);
        fastfalle(delay);
        spacefall(space,delay);
        rotationofblock(rotate);
        for(int  i = 0;i<M;i++)
        deleteline(M,N,lineduring1fall);
        scorecounting(lineduring1fall,score);    
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
         
        sf:: RectangleShape cell(sf::Vector2f(100, 100));
        cell.setPosition(CELL_SIZE*42,CELL_SIZE*10);
        cell.setFillColor(sf::Color(100,100,100));
        
        sf:: RectangleShape preview_top(sf::Vector2f(100, 5));
        preview_top.setFillColor(sf::Color(255,255,255));
        preview_top.setOutlineThickness(0); 
        preview_top.setPosition(CELL_SIZE*42, CELL_SIZE*10);
        
        sf:: RectangleShape preview_bot(sf::Vector2f(100, 5));
        preview_bot.setFillColor(sf::Color(255,255,255));
        preview_bot.setOutlineThickness(0); 
        preview_bot.setPosition(CELL_SIZE*42, CELL_SIZE*22);
        
        window.draw(cell);
        window.draw(preview_top);
        window.draw(preview_bot);
        
        
          
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    cout<<"Your score for the game is : "<<score<<endl;
    cout<<"Thank you\nGAMEOVER\n";
    menu();
    return 0;
}

//<--for hard level-->//

int hard(){    
    srand(time(0));
    RenderWindow window(sf::VideoMode(450,420), title);
    Texture obj1, obj2, obj3, obj4;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/bomb.png");
    
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    Sprite sprite(obj1), background(obj2), frame(obj3), sprite1(obj4);
    int delta_x=0, colorNum=1, caser = 0, CELL_SIZE = 8, lineduring1fall = 0,score= 0;
    float timer=0, delay=0.1;
    bool rotate=0, linefull=0, space = 0, pause = 0;
    Clock clock;


    while (window.isOpen()){
           
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
                else if (e.key.code == Keyboard::Space)
                   space = true;
                else if (e.key.code == Keyboard::H)
                   {
                    if(pause)
                     pause=false;
                    else
                     pause = true;
                   }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
            
        if (pause){
         continue;
         }
        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
        linefull = Gameover(M,N);
        if(linefull)
        break;
        fallingPiece(timer, delay, colorNum);               //Example: fallingPiece() function is called here
        movementofblocks(delta_x);
        fastfallh(delay);
        spacefall(space,delay);
        rotationofblock(rotate);
        for(int  i = 0;i<M;i++)
        deleteline(M,N,lineduring1fall);
        scorecounting(lineduring1fall,score);    
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////


        window.clear(Color::Black);
        window.draw(background);
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
          }
         
        sf:: RectangleShape cell(sf::Vector2f(100, 100));
        cell.setPosition(CELL_SIZE*42,CELL_SIZE*10);
        cell.setFillColor(sf::Color(100,100,100));
        
        sf:: RectangleShape preview_top(sf::Vector2f(100, 5));
        preview_top.setFillColor(sf::Color(255,255,255));
        preview_top.setOutlineThickness(0); 
        preview_top.setPosition(CELL_SIZE*42, CELL_SIZE*10);
        
        sf:: RectangleShape preview_bot(sf::Vector2f(100, 5));
        preview_bot.setFillColor(sf::Color(255,255,255));
        preview_bot.setOutlineThickness(0); 
        preview_bot.setPosition(CELL_SIZE*42, CELL_SIZE*22);
        
        window.draw(cell);
        window.draw(preview_top);
        window.draw(preview_bot);
        
        
          
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    cout<<"Your score for the game is : "<<score<<endl;
    cout<<"Thank you\nGAMEOVER\n";
    menu();
    return 0;
}


//-lsfml-graphics -lsfml-window -lsfml-system -Wfatal-errors
//Can use static_cast<float>(x * gridSize);

/* 
FOR USE WITH ANIMATION CLASS 
Character
sf::Sprite myCharacter;

Load the image...
Animation animation(myCharacter);
animation.addFrame({sf::IntRect(x,y,w,h), 0.1});
do this for as many frames as you need

In your main loop:
animation.update(elapsed);
window.draw(myCharacter);
*/

/*
MAKE TILE
sf::Texture boxTexture;
if (!boxTexture.loadFromFile("RTS_Crate.png")) cout << "[Can't load texture]";
sf::Sprite boxSprite;
boxSprite.setTexture(boxTexture);
sf::Vector2f boxPosition(0.f, 0.f);
boxSprite.setPosition(boxPosition);
boxSprite.scale(0.625, 0.625);
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

void showString(sf::RenderWindow &window, sf::Font& font, std::string text, sf::Vector2f position, sf::Color color)
{ 
    sf::Text myText(text, font);
    myText.setCharacterSize(20);
    myText.setFillColor(color);
    myText.setPosition(position);
    window.draw(myText);
};

int main(){

    sf::RenderWindow window(sf::VideoMode(320, 320), "DUNGEON");    

    //Tile Map Texture
    sf::Texture dungeonTileSet;
    if (!dungeonTileSet.loadFromFile("Dungeon_Tileset.png")){
        cout << "[Can't load Tileset texture]";
        return 1;
    };

    sf::Sprite spriteArrayTile[10];
    spriteArrayTile[0].setTexture(dungeonTileSet);
    spriteArrayTile[0].setTextureRect(sf::IntRect(144,0,16,16));
    spriteArrayTile[0].scale(2.f,2.f);
    

    // Floor Tile
    sf::Texture floorTexture;
    if (!floorTexture.loadFromFile("Dungeon_Tileset.png", sf::IntRect(144,0,16,16))) cout << "[Can't load floor texture]";
    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture);
    sf::Vector2f floorPosition(0.f, 0.f);
    floorSprite.scale(2.f, 2.f);

    // Left Wall Tile
    sf::Texture leftWallTexture;
    if (!leftWallTexture.loadFromFile("Dungeon_Tileset.png", sf::IntRect(0,0,16,16))) cout << "[Can't load left wall texture]";
    sf::Sprite leftWallSprite;
    leftWallSprite.setTexture(leftWallTexture);
    sf::Vector2f leftWallPosition(0.f, 0.f);
    leftWallSprite.scale(2.f, 2.f);

    // Right Wall Tile
    sf::Texture rightWallTexture;
    if (!rightWallTexture.loadFromFile("Dungeon_Tileset.png", sf::IntRect(80,0,16,16))) cout << "[Can't load right wall texture]";
    sf::Sprite rightWallSprite;
    rightWallSprite.setTexture(rightWallTexture);
    sf::Vector2f rightWallPosition(0.f, 0.f);
    rightWallSprite.scale(2.f, 2.f);

    // Top Wall Tile
    sf::Texture topWallTexture;
    if (!topWallTexture.loadFromFile("Dungeon_Tileset.png", sf::IntRect(32,0,16,16))) cout << "[Can't load top wall texture]";
    sf::Sprite topWallSprite;
    topWallSprite.setTexture(topWallTexture);
    sf::Vector2f topWallPosition(0.f, 0.f);
    topWallSprite.scale(2.f, 2.f);

    //Bottom Wall Tile 
    sf::Texture bottomWallTexture;
    if (!bottomWallTexture.loadFromFile("Dungeon_Tileset.png", sf::IntRect(10,0,16,16))) cout << "[Can't load bottom wall texture]";
    sf::Sprite bottomWallSprite;
    bottomWallSprite.setTexture(bottomWallTexture);
    sf::Vector2f bottomWallPosition(0.f, 0.f);
    bottomWallSprite.scale(2.f, 2.f);

    //View
    sf::View view;
    view.reset(sf::FloatRect(100, 200, 100, 100));
    // window.setView(view);

    // Font
    sf::Font myFont;
    if (!myFont.loadFromFile("arial.ttf"))
    {
        cout << "Error loading file \"arial.ttf\"";
        return 0; 
    }

    // Music
    sf::Music music;
    if (!music.openFromFile("gameMusic.ogg")) return -1; // error
    
    bool mainMenu = false;

    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("character.png", sf::IntRect(0,0,32,32))) cout << "[Can't load character texture]";
    sf::Sprite characterSprite;
    sf::Vector2f characterPosition(0.f,0.f);
    characterSprite.setPosition(characterPosition);

    //Map
    int map[10][10] = {
        { 2,4,4,4,4,4,4,4,4,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,0,0,0,0,0,0,0,0,3 },
        { 2,5,5,5,0,0,5,5,5,3 },
    };

    //Game Loop    
    while(window.isOpen())
    {
        music.play();

        // Events
        sf::Event ev;
        while(window.pollEvent(ev)){
            
            if(ev.type == sf::Event::Closed) window.close();

            if (ev.mouseButton.button == sf::Mouse::Left)
            {
                // std::cout << "the right button was pressed" << std::endl;
                // std::cout << "mouse x: " << ev.mouseButton.x << std::endl;
                // std::cout << "mouse y: " << ev.mouseButton.y << std::endl;
            }
        }
    
        window.clear();

        if(mainMenu == true){
           showString(window, myFont, "Dungeon", sf::Vector2f(100,100), sf::Color::Blue);
        }   

        //Draw grid if menu is false
        if(mainMenu == false){
            int gridSize = 32;
            for (int x = 0; x < 10; x++)
            {
                for (int y = 0; y < 10; y++)
                {   
                    if (map[x][y] == 0) { // Floor
                        floorSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                        window.draw(floorSprite);
                    }   
                    // if (map[x][y] == 1) { // Floor
                    //     floorSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                    //     window.draw(floorSprite);
                    // } 
                    if (map[x][y] == 2) { // Left Wall
                        leftWallSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                        window.draw(leftWallSprite);
                    }   
                    if (map[x][y] == 3) { // Right Wall
                        rightWallSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                        window.draw(rightWallSprite);
                    } 
                    if (map[x][y] == 4) { // Top Wall
                        topWallSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                        window.draw(topWallSprite);
                    } 
                    if (map[x][y] == 5) { // Bottom Wall
                        bottomWallSprite.setPosition(sf::Vector2f(y * gridSize, x * gridSize));
                        window.draw(bottomWallSprite);
                    } 
                }  
            }
        };

        window.draw(spriteArrayTile[0]);
        window.display();

    };

    return 0;
};


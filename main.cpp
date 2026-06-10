#include"display_battle.hpp"
#include"graphics_object_card.hpp"
#include"graphics_object_character.hpp"
#include"graphics_object_end_turn.hpp"
#include"GameMaster.h"
#include "Player.h"
#include "Card.h"
#include "Enemy.h"
#include "Battle.h"


int main(){
    srand(time(NULL));

    CardFactory::Initialize();
    EnemyFactory::Initialize();
    
    sf::RenderWindow window(sf::VideoMode({1800, 1000}), "Giereczka");
    GameMaster Game_Master(&window);
    bool left_mouse_clicked = false;
    int mouse_x = 0;
    int mouse_y = 0;

    // run the program as long as the window is open
        while(window.isOpen())
        {
            // check all the window's events that were triggered since the last iteration of the loop
            sf::Event event;
            while (window.pollEvent(event))
            {
                // "close requested" event: we close the window
                if(event.type == sf::Event::Closed){
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) 
                {
                    if (event.mouseButton.button == sf::Mouse::Left) 
                    {
                        mouse_x = event.mouseButton.x;
                        mouse_y = event.mouseButton.y;
                        left_mouse_clicked = true;
                    }
                }
            }

            Game_Master.Update_And_Render(mouse_x, mouse_y, left_mouse_clicked);
            left_mouse_clicked = false;

            window.display();
        }


	return 0;
}
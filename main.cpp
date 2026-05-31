#include"display_battle.hpp"
#include"graphics_object_card.hpp"
#include"graphics_object_character.hpp"
#include"graphics_object_end_turn.hpp"
#include "Player.h"
#include "Card.h"
#include "Enemy.h"
#include "Battle.h"

int main(){
    srand(time(NULL));
	//-------------------------------------
	CardFactory::regist(1, &AttackCard::kreator);
	CardFactory::regist(2, &ShieldCard::kreator);
	CardFactory::regist(3, &AttackShieldCard::kreator);
    CardFactory::regist(4, &DrawCard::kreator);
	
	Card* BasicAttack = CardFactory::create(1, "BasicAttack", 1);
	Card* BasicShield = CardFactory::create(2, "BasicShield", 1);
	Card* BasicAttackShield = CardFactory::create(3, "BasicAttackShield", 1);
    Card* DrawCard = CardFactory::create(4, "Draw Card", 0);
	//-------------------------------------

	//-------------------------------------
	EnemyFactory::regist(1, &BasicEnemy::kreator);

	Enemy* BasicEnemy = EnemyFactory::create(1, "BasicEnemy", 25);
	std::vector<Enemy*> Act_Enemies;
	Act_Enemies.push_back(BasicEnemy);
	//-------------------------------------

	PlayerCharacter g("Pimpek", 20);
	
	//-------------------------------------
	Player Gracz;
	Gracz.Add_Card(BasicAttack);
    Gracz.Add_Card(DrawCard);
	Gracz.Set_Character(g);
	//-------------------------------------
	
    graphics_object_end_turn end;
    graphics_object_energy_counter e_counter;

    // create the window
    sf::RenderWindow window(sf::VideoMode({1800, 1000}), "Giereczka");
    Battle b(&Gracz, Act_Enemies, &window, &end, &e_counter);

    /*
    graphics_object_card MOJA_KARTA("Karcioszka", "1", "fajny tekst,\nno zajebisty nawet \nmozna wrappowac", ".resources/textures/cry.jpg", 20, 20);
    graphics_object_card AHA("HAHA", "3", "piach?", ".resources/textures/aaa.jpg", 20, 400, 255, 255, 0, 255);
    graphics_object_end_turn bum;
    graphics_object_character czesio("Czesio", ".resources/textures/cry.jpg", 300, 300, 800, 200);
    std::vector<graphics_object_card> objects;
    objects.push_back(MOJA_KARTA);
    objects.push_back(AHA);
    */

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
                        int x = event.mouseButton.x;
                        int y = event.mouseButton.y;
                        b.Handle_Mouse_Click(x, y);
                    }
                }
            }

            // clear the window with white color
            window.clear(sf::Color::White);
            
            //rysowanie:
            sf::Vector2u window_size = window.getSize();

            //rysowanie kart:
            b.Render_Cards();

            //rysowanie postaci:
            //gracz:
            b.Render_Player();

            //wrogowie:
            b.Render_Enemies();

            //licznik energii:
            b.Render_Energy_Counter();

            //przycisk konca tury:
            b.Render_End_Turn_Button();

            //highlightowanie kursorem:
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            
            b.EnemyAction();
            // end the current frame
            window.display();
        }


	return 0;
}
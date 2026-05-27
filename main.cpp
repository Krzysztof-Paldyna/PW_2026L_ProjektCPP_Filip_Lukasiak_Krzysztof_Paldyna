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
	
	Card* BasicAttack = CardFactory::create(1, "BasicAttack", 1);
	Card* BasicShield = CardFactory::create(2, "BasicShield", 1);
	Card* BasicAttackShield = CardFactory::create(3, "BasicAttackShield", 1);
	//-------------------------------------

	//-------------------------------------
	EnemyFactory::regist(1, &BasicEnemy::kreator);

	Enemy* BasicEnemy = EnemyFactory::create(1, "BasicEnemy", 25);
	std::vector<Enemy> Act_Enemies;
	Act_Enemies.push_back(*BasicEnemy);
	//-------------------------------------

	PlayerCharacter g("Pimpek", 20);
	
	//-------------------------------------
	Player Gracz;
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicAttack);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicShield);
	Gracz.Add_Card(BasicAttackShield);
	Gracz.Add_Card(BasicAttackShield);
	Gracz.Set_Character(g);
	//-------------------------------------
	Battle b(&Gracz, Act_Enemies);
	//b.PlayerTurn();

    // create the window
    sf::RenderWindow window(sf::VideoMode({1800, 1000}), "Giereczka");
    sf::Font card_font;
    card_font.loadFromFile(".resources/fonts/Andale_Mono.ttf");

    //DO PRZEROBIENIA: UPDATE TEKSTUR:
    for(auto &v : b.Return_Player()->Return_PlayerHand()){
        v->update_texture();
    }
    for(auto &v : b.Return_Enemies()){
        v.update_texture();
    }
    b.Return_Player()->Return_Character().update_texture();

    //startowy damage dla pokazu:
    auto hp = b.Return_Enemies().at(0).Return_CurrentHP();
    b.Return_Enemies().at(0).Set_CurrentHP(hp - 5);
    b.Return_Enemies().at(0).set_hp(hp - 5);

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
            }

            // clear the window with white color
            window.clear(sf::Color::White);
            
            //rysowanie:
            sf::Vector2u window_size = window.getSize();

            //rysowanie kart:
            int cards_on_hand = b.Return_Player()->Return_PlayerHand().size();
            for(int i = 0; i < cards_on_hand; ++i){
                auto card = b.Return_Player()->Return_PlayerHand().at(i);
                card->set_position(int((window_size.x / (cards_on_hand + 1) * (i + 1) - card->get_dim_x()/2)), int(window_size.y - card->get_dim_y() - 10));
                card->draw(window, card_font);
            }

            //rysowanie postaci:
            //gracz:
            auto player = b.Return_Player()->Return_Character();
            player.set_position(int(window_size.x / 6 - player.get_dim_x()/2), int (window_size.y / 4));
            player.draw(window, card_font);

            //wrogowie:
            int enemy_count = b.Return_Enemies().size();
            for(int i = 0; i < enemy_count; ++i){
                auto enemy = b.Return_Enemies().at(i);
                enemy.set_position(int(window_size.x / 2 * (1 + 1/((enemy_count + 1) * (i + 1))) + enemy.get_dim_x()), int(window_size.y / 4));
                enemy.draw(window, card_font);
            }

            //highlightowanie kursorem:
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            for(auto &v : b.Return_Player()->Return_PlayerHand()){
                int x = v->get_x();
                int y = v->get_y();
                int dim_x = v->get_dim_x();
                int dim_y = v->get_dim_y();
                if(mousePosition.x >= x && mousePosition.x <= x + dim_x && mousePosition.y >= y && mousePosition.y <= y + dim_y){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        v->set_highlight_state(highlight::positive);
                    }
                }
                else{
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                        v->set_highlight_state(highlight::none);
                    }
                }
            }
            // end the current frame
            window.display();
        }

    b.PlayerTurn();

	return 0;
}